// Etape 5 : predire l'orientation de l'image suivante.
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKMath/NkQuat.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace nkentseu;

NkVec3f VitesseAngulaire(const NkQuatf &from, const NkQuatf &to, float32 dtSeconds)
{
    if (dtSeconds <= 0.f) return NkVec3f(0.f, 0.f, 0.f);
    NkQuatf delta = (to * from.Conjugate()).Normalized();
    if (delta.w < 0.f) delta = NkQuatf(-delta.x, -delta.y, -delta.z, -delta.w);
    const float32 angleRad = delta.Angle().Rad();
    if (angleRad <= 1e-6f) return NkVec3f(0.f, 0.f, 0.f);
    return delta.Axis() * (angleRad / dtSeconds);
}

NkQuatf Extrapoler(const NkQuatf &orientation, const NkVec3f &vitesse, float32 dtSeconds)
{
    const float32 speedRad = vitesse.Len();
    if (speedRad <= 1e-6f) return orientation;
    const NkVec3f axis = vitesse * (1.f / speedRad);
    const NkQuatf delta(NkAngle::FromRad(speedRad * dtSeconds), axis);
    return (delta * orientation).Normalized();
}

int nkmain(const NkEntryState &)
{
    const char *hzText = getenv("MASALLE_HZ");
    const uint64 hz = (hzText && hzText[0]) ? strtoull(hzText, nullptr, 10) : 60;
    const float32 period = 1.f / static_cast<float32>(hz ? hz : 60);

    float64 lacetRad = 0.0;
    float64 tangageRad = 0.0;
    float64 sourisDX = 0.0;
    float64 sourisDY = 0.0;

    NkQuatf precedente;
    NkQuatf gardee;
    NkQuatf prediction;
    bool premiere = true;

    double sommeAvec = 0.0, sommeSans = 0.0;
    double maxAvec = 0.0, maxSans = 0.0;
    uint64 immobiles = 0;
    uint64 comparaison = 0;

    // Dans la boucle d'affichage, traiter NkMouseRawEvent et NkMouseMoveEvent,
    // accumuler les mouvements puis mettre lacet/tangage a jour une fois par image.
    // L'extrapolation et les mesures ci-dessous portent sur les images 1 a 1000.
    for (uint64 i = 0; i < 1001 && comparaison < 1000; ++i) {
        const NkMat4f rotation = NkMat4f::RotationY(NkAngle::FromRad(static_cast<float32>(lacetRad)))
            * NkMat4f::RotationX(NkAngle::FromRad(static_cast<float32>(tangageRad)));
        const NkQuatf orientation = NkQuatf(rotation).Normalized();

        if (!premiere) {
            const float32 erreurAvec = (orientation * prediction.Conjugate()).Normalized().Angle().Deg();
            const float32 erreurSans = (orientation * gardee.Conjugate()).Normalized().Angle().Deg();
            if (erreurSans < 1e-3f) ++immobiles;
            sommeAvec += erreurAvec;
            sommeSans += erreurSans;
            maxAvec = std::max(maxAvec, static_cast<double>(erreurAvec));
            maxSans = std::max(maxSans, static_cast<double>(erreurSans));
            ++comparaison;
        }

        const NkVec3f vitesse = premiere ? NkVec3f(0.f, 0.f, 0.f)
                                         : VitesseAngulaire(precedente, orientation, period);
        prediction = Extrapoler(orientation, vitesse, period);
        gardee = orientation;
        precedente = orientation;
        premiere = false;
    }

    std::printf("avec prediction : moyenne %.3f deg, max %.3f deg, sur %llu images\n",
                sommeAvec / comparaison, maxAvec, static_cast<unsigned long long>(comparaison));
    std::printf("sans prediction : moyenne %.3f deg, max %.3f deg, sur %llu images\n",
                sommeSans / comparaison, maxSans, static_cast<unsigned long long>(comparaison));
    return 0;
}
