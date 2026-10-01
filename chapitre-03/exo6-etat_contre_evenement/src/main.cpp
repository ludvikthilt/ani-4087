#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>



static void AfficherHorodatage()
{
    using clock = std::chrono::system_clock;
    auto now = clock::now();
    std::time_t t = clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) % 1000;

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::cout << "[" << std::put_time(&tm, "%H:%M:%S") << "."
              << std::setfill('0') << std::setw(3) << ms.count()
              << std::setfill(' ') << "] ";
}

// Compteur 1 (ETAT) : appele une fois par image.
// Il s'incremente si Espace est tenue a cet instant.
static void CompterEtat(int& compteurEtat, int numeroImage)
{
    if (nkentseu::NkInput.IsKeyDown(nkentseu::NkKey::NK_SPACE)) {
        ++compteurEtat;
        AfficherHorodatage();
        std::cout << "ETAT      image " << numeroImage
                  << " : Espace tenue (total " << compteurEtat << ")" << std::endl;
    }
}

// Compteur 2 (EVENEMENT) : appele pour chaque NkKeyPressEvent.
// Il s'incremente seulement si la touche est Espace.
static void CompterEvenement(nkentseu::NkKeyPressEvent* keyEvent, int& compteurEvenement)
{
    if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESPACE) {
        ++compteurEvenement;
        AfficherHorodatage();
        std::cout << "EVENEMENT NkKeyPressEvent Espace (total "
                  << compteurEvenement << ")" << std::endl;
    }
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

    bool running = true;
    auto& stackEvent = nkentseu::NkEvents();

    int compteurEtat = 0;
    int compteurEvenement = 0;
    int numeroImage = 0;

    while (running) {
        ++numeroImage;

        // Voie evenement : tous les evenements en attente
        nkentseu::NkEvent* event;
        while ((event = stackEvent.PollEvent()) != nullptr) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }

            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);

                /*if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                    running = false;
                }*/

                CompterEvenement(keyEvent, compteurEvenement);
            }
        }

        // Voie etat : une seule lecture par image, hors de la boucle d'evenements
        CompterEtat(compteurEtat, numeroImage);
    }

    std::cout << "\nImages totales                       : " << numeroImage << std::endl;
    std::cout << "Compteur 1 (etat, IsKeyDown)         : " << compteurEtat << std::endl;
    std::cout << "Compteur 2 (evenement, KeyPressEvent): " << compteurEvenement << std::endl;

    return 0;
}
