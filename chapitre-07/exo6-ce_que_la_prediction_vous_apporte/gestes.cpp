// Exercice 6 : ce que la prediction apporte
#include "NKWindow/NKMain.h"
#include "NKMath/NkQuat.h"
#include <cstdio>
#include <cmath>

using namespace nkentseu;
using namespace nkentseu::math;

static NkVec3f VitesseAngulaire(const NkQuatf &from, const NkQuatf &to, float32 dtSeconds)
{
    if (dtSeconds <= 0.f) return NkVec3f(0.f, 0.f, 0.f);
    NkQuatf delta = (to * from.Conjugate()).Normalized();
    if (delta.w < 0.f)
        delta = NkQuatf(-delta.x, -delta.y, -delta.z, -delta.w);
    const float32 angleRad = delta.Angle().Rad();
    if (angleRad <= 1e-6f) return NkVec3f(0.f, 0.f, 0.f);
    return delta.Axis() * (angleRad / dtSeconds);
}

static NkQuatf Extrapoler(const NkQuatf &orientation, const NkVec3f &vitesse, float32 dtSeconds)
{
    const float32 speedRad = vitesse.Len();
    if (speedRad <= 1e-6f) return orientation;
    const NkVec3f axis = vitesse * (1.f / speedRad);
    NkQuatf delta(NkAngle::FromRad(speedRad * dtSeconds), axis);
    return (delta * orientation).Normalized();
}

static double Lacet(double t, double amplitude, double duree)
{
    if (t <= 0.0) return 0.0;
    if (t >= duree) return amplitude;
    const double kPi = 3.14159265358979323846;
    return amplitude * 0.5 * (1.0 - std::cos(kPi * t / duree));
}

int nkmain(const NkEntryState &)
{
    const float64 hz = 72.0;
    const float32 period = static_cast<float32>(1.0 / hz);

    struct Geste { const char *nom; double amplitude; double duree; };
    const Geste gestes[] = {
        {"lent", 45.0, 0.800},
        {"rapide", 90.0, 0.400},
        {"demi-tour brusque", 180.0, 0.300}
    };

    for (const Geste &g : gestes) {
        double sommeAvec = 0.0, sommeSans = 0.0;
        uint64 count = 0;
        NkQuatf precedente;
        NkQuatf courante;
        bool first = true;

        const uint64 lastSample = static_cast<uint64>(std::floor(g.duree * hz));
        for (uint64 n = 0; n <= lastSample; ++n) {
            const double t = static_cast<double>(n) / hz;
            const double angleDeg = Lacet(t, g.amplitude, g.duree);
            courante = NkQuatf::RotateY(NkAngle(angleDeg));

            if (!first && n + 1 <= lastSample) {
                const double dt = static_cast<double>(n) / hz - static_cast<double>(n - 1) / hz;
                const NkVec3f vitesse = VitesseAngulaire(precedente, courante, static_cast<float32>(dt));
                const NkQuatf prediction = Extrapoler(courante, vitesse, period);

                const double tNext = static_cast<double>(n + 1) / hz;
                const double angleNext = Lacet(tNext, g.amplitude, g.duree);
                const NkQuatf vraie = NkQuatf::RotateY(NkAngle(angleNext));

                const float32 avec = (vraie * prediction.Conjugate()).Normalized().Angle().Deg();
                const float32 sans = (vraie * courante.Conjugate()).Normalized().Angle().Deg();
                sommeAvec += avec;
                sommeSans += sans;
                ++count;
            }

            precedente = courante;
            first = false;
        }

        const double moyenneAvec = count ? sommeAvec / count : 0.0;
        const double moyenneSans = count ? sommeSans / count : 0.0;
        const double rapport = moyenneAvec > 1e-9 ? moyenneSans / moyenneAvec : 0.0;
        std::printf("%s (%.0f deg en %.0f ms) : avec %.3f deg, sans %.3f deg, rapport %.2f\\n",
                    g.nom, g.amplitude, g.duree * 1000.0,
                    moyenneAvec, moyenneSans, rapport);
    }
    return 0;
}
