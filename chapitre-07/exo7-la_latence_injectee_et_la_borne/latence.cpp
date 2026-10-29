// Exercice 7 : la latence injectee et sa borne
#include "NKWindow/NKMain.h"
#include "NKMath/NkQuat.h"
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace nkentseu;
using namespace nkentseu::math;

static const uint32 kMaxSamples = 64;
struct PoseSample { float64 time; NkQuatf pose; float32 velocityY; };

static double Lacet(double t)
{
    const double start = 1.0, amplitude = 98.0, duration = 0.400;
    const double local = t - start;
    const double kPi = 3.14159265358979323846;
    if (local <= 0.0) return 0.0;
    if (local >= duration) return amplitude;
    return amplitude * 0.5 * (1.0 - std::cos(kPi * local / duration));
}

static NkVec3f VitesseAngulaire(const NkQuatf &from, const NkQuatf &to, float32 dtSeconds)
{
    if (dtSeconds <= 0.f) return NkVec3f(0.f, 0.f, 0.f);
    NkQuatf delta = (to * from.Conjugate()).Normalized();
    if (delta.w < 0.f) delta = NkQuatf(-delta.x, -delta.y, -delta.z, -delta.w);
    const float32 angleRad = delta.Angle().Rad();
    if (angleRad <= 1e-6f) return NkVec3f(0.f, 0.f, 0.f);
    return delta.Axis() * (angleRad / dtSeconds);
}

static NkQuatf Extrapoler(const NkQuatf &pose, const NkVec3f &velocity, float32 dtSeconds)
{
    const float32 speed = velocity.Len();
    if (speed <= 1e-6f) return pose;
    const NkVec3f axis = velocity * (1.f / speed);
    const NkQuatf delta(NkAngle::FromRad(speed * dtSeconds), axis);
    return (delta * pose).Normalized();
}

static float32 Yaw(const NkQuatf &q)
{
    return 2.f * std::atan2((double)q.y, (double)q.w) * 180.f / 3.14159265358979323846f;
}

class History {
    PoseSample samples_[64]{};
    uint32 head_ = 0;
    uint32 count_ = 0;
public:
    void Push(float64 time, const NkQuatf &pose)
    {
        float32 velocity = 0.f;
        if (count_ > 0) {
            const uint32 previous = (head_ + kMaxSamples - 1u) % kMaxSamples;
            const float32 dt = static_cast<float32>(time - samples_[previous].time);
            velocity = VitesseAngulaire(samples_[previous].pose, pose, dt).y;
        }
        samples_[head_] = {time, pose, velocity};
        head_ = (head_ + 1u) % kMaxSamples;
        if (count_ < kMaxSamples) ++count_;
    }
    PoseSample RenderAt(float64 now, float64 latency) const
    {
        const float64 target = now - latency;
        uint32 index = (head_ + kMaxSamples - 1u) % kMaxSamples;
        for (uint32 i = 0; i < count_; ++i) {
            if (samples_[index].time <= target) return samples_[index];
            index = (index + kMaxSamples - 1u) % kMaxSamples;
        }
        return samples_[index];
    }
};

int nkmain(const NkEntryState &)
{
    const double hz = 72.0;
    const float32 period = static_cast<float32>(1.0 / hz);
    History history;
    for (uint64 i = 0; i <= 116; ++i) {
        const double t = static_cast<double>(i) / hz;
        history.Push(t, NkQuatf::RotateY(NkAngle(Lacet(t))));
    }

    const double latencies[] = {0.010, 0.020, 0.050, 0.100, 0.200};
    for (double latency : latencies) {
        std::printf("latence %.0f ms\n", latency * 1000.0);
    }

    PoseSample unbounded = history.RenderAt(1.2, 1.0);
    const float32 horizonSeconds = static_cast<float32>(1.2 + period - unbounded.time);
    const NkQuatf predicted = Extrapoler(unbounded.pose,
        NkVec3f(0.f, unbounded.velocityY, 0.f), horizonSeconds);
    std::printf("sans borne : echantillon a %.3f s, horizon %.0f ms, predit %.3f deg, vrai %.3f deg\n",
        unbounded.time, horizonSeconds * 1000.f, Yaw(predicted), Lacet(1.2 + period));

    float32 boundedHorizon = horizonSeconds;
    if (boundedHorizon > 0.1f) boundedHorizon = 0.1f;
    if (boundedHorizon < -0.1f) boundedHorizon = -0.1f;
    const NkQuatf bounded = Extrapoler(unbounded.pose,
        NkVec3f(0.f, unbounded.velocityY, 0.f), boundedHorizon);
    std::printf("avec borne : echantillon a %.3f s, horizon %.0f ms, predit %.3f deg, vrai %.3f deg\n",
        unbounded.time, boundedHorizon * 1000.f, Yaw(bounded), Lacet(1.2 + period));
    return 0;
}
