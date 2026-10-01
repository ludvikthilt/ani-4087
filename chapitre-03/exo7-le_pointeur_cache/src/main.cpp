#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include <iostream>
#include <vector>

// Cacher / confiner le curseur : appels Win32 directs (Windows uniquement).
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
#endif

NKENTSEU_DEFINE_APP_DATA(([](){
    nkentseu::NkAppData d{};
    d.appName = "La Fenetre Nue";
    d.appVersion = "0.1.0";
    return d;
})())

// Definition de la saturation :
// la position (x, y) ne change plus alors que la souris bouge encore
// (rawDelta non nul), pendant SEUIL images de suite.
constexpr int SEUIL = 3;

struct Image {
    int numero;
    int x, y;       // position du curseur
    int dx, dy;     // somme des rawDelta recus pendant cette image
};

static void CacherEtConfiner()
{
#ifdef _WIN32
    HWND hwnd = GetActiveWindow();
    if (hwnd == nullptr) {
        hwnd = GetForegroundWindow();
    }
    if (hwnd == nullptr) {
        std::cout << "Fenetre native introuvable : curseur ni cache ni confine." << std::endl;
        return;
    }

    // Confiner : on restreint le curseur a la zone client, en coordonnees ecran
    RECT zone;
    GetClientRect(hwnd, &zone);
    MapWindowPoints(hwnd, nullptr, reinterpret_cast<POINT*>(&zone), 2);
    ClipCursor(&zone);

    // Cacher : ShowCursor tient un compteur, on le descend jusqu'a "cache"
    while (ShowCursor(FALSE) >= 0) {}
#else
    std::cout << "Cacher/confiner : seulement implemente pour Windows ici." << std::endl;
#endif
}

static void LibererCurseur()
{
#ifdef _WIN32
    ClipCursor(nullptr);
    while (ShowCursor(TRUE) < 0) {}
#endif
}

int nkmain(const nkentseu::NkEntryState &state)
{
    nkentseu::NkWindowConfig config;
    config.title = "La Fenetre Nue";
    config.width = 1000;
    config.height = 720;

    nkentseu::NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    CacherEtConfiner();

    bool running = true;
    auto& stackEvent = nkentseu::NkEvents();

    int posX = 0, posY = 0;
    int precX = 0, precY = 0;

    std::vector<Image> historique;
    int numeroImage = 0;

    int serie = 0;                 // images consecutives "position figee, souris en mouvement"
    int sommeApresX = 0;           // somme des rawDelta APRES l'image de saturation
    int sommeApresY = 0;
    bool saturation = false;
    int imageSaturation = 0;

    while (running) {
        ++numeroImage;
        int dxImage = 0, dyImage = 0;

        nkentseu::NkEvent* event;
        while ((event = stackEvent.PollEvent()) != nullptr) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }

            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                    running = false;
                }
            }

            if (event->Is<nkentseu::NkMouseMoveEvent>()) {
                auto* moveEvent = static_cast<nkentseu::NkMouseMoveEvent*>(event);
                posX = moveEvent->GetX();
                posY = moveEvent->GetY();
            }

            if (event->Is<nkentseu::NkMouseRawEvent>()) {
                auto* rawEvent = static_cast<nkentseu::NkMouseRawEvent*>(event);
                dxImage += rawEvent->GetDeltaX();
                dyImage += rawEvent->GetDeltaY();
            }
        }

        historique.push_back({numeroImage, posX, posY, dxImage, dyImage});

        std::cout << "image " << numeroImage
                  << " | x=" << posX << " y=" << posY
                  << " | rawDelta=(" << dxImage << ", " << dyImage << ")"
                  << std::endl;

        // ---- Detection de la saturation ----
        bool positionFigee = (posX == precX && posY == precY);
        bool sourisBouge   = (dxImage != 0 || dyImage != 0);

        if (!saturation) {
            if (positionFigee && sourisBouge) {
                ++serie;
                if (serie > 1) {          // l'image qui debute la serie est exclue de la somme
                    sommeApresX += dxImage;
                    sommeApresY += dyImage;
                }
                if (serie >= SEUIL) {
                    saturation = true;
                    imageSaturation = numeroImage - SEUIL + 1;
                    std::cout << ">>> SATURATION detectee, image " << imageSaturation << std::endl;
                }
            } else {
                serie = 0;
                sommeApresX = 0;
                sommeApresY = 0;
            }
        } else {
            sommeApresX += dxImage;
            sommeApresY += dyImage;
        }

        precX = posX;
        precY = posY;
    }

    // On libere le curseur avant d'afficher le resultat
    LibererCurseur();

    // ---- Resultat ----
    std::cout << "\n===== RESULTAT =====" << std::endl;
    if (!saturation) {
        std::cout << "Aucune saturation detectee (le curseur n'a pas atteint le bord, "
                     "ou rawDelta est reste a 0)." << std::endl;
        return 0;
    }

    const Image& sat   = historique[imageSaturation - 1];
    const Image& apres = historique[imageSaturation];   // image suivante

    std::cout << "Image de saturation       : " << sat.numero
              << " | x=" << sat.x << " y=" << sat.y
              << " | rawDelta=(" << sat.dx << ", " << sat.dy << ")" << std::endl;
    std::cout << "Image apres saturation    : " << apres.numero
              << " | x=" << apres.x << " y=" << apres.y
              << " | rawDelta=(" << apres.dx << ", " << apres.dy << ")" << std::endl;
    std::cout << "Somme rawDelta apres sat. : (" << sommeApresX << ", " << sommeApresY << ")" << std::endl;

    return 0;
}
