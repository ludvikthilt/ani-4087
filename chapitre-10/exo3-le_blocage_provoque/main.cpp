#include <iostream>
#include <string>

int main() {
    std::string policy;
    int imageCount = 0;
    if (!(std::cin >> policy >> imageCount)) {
        return 0;
    }

    std::string renderFlags;
    if (imageCount > 0) {
        std::cin >> renderFlags;
    }

    bool frameOpen = false;
    int rendered = 0;
    int lost = 0;
    int errors = 0;
    int firstWaitRefusal = 0;

    for (int image = 1; image <= imageCount; ++image) {
        bool shouldRender = false;
        bool waitAccepted = !frameOpen;
        if (waitAccepted) {
            shouldRender =
                renderFlags[static_cast<std::size_t>(image - 1)] == '1';
        } else {
            ++errors;
            if (firstWaitRefusal == 0) {
                firstWaitRefusal = image;
            }
        }

        const bool beginAccepted = !frameOpen;
        if (!beginAccepted) {
            ++errors;
        } else {
            frameOpen = true;
        }

        const bool didRender = shouldRender && beginAccepted;
        if (didRender) {
            ++rendered;
        } else if (!waitAccepted &&
                   renderFlags[static_cast<std::size_t>(image - 1)] == '1') {
            ++lost;
        }

        std::string endResult = "-";
        const bool callsEnd = policy == "TOUJOURS" || didRender;
        if (callsEnd) {
            if (frameOpen) {
                frameOpen = false;
                endResult = "OK";
            } else {
                ++errors;
                endResult = "REFUSE";
            }
        }

        std::cout << image << ' '
                  << (waitAccepted ? "OK" : "REFUSE") << ' '
                  << (beginAccepted ? "OK" : "REFUSE") << ' '
                  << (didRender ? "OUI" : "NON") << ' ' << endResult << '\n';
    }

    std::cout << "RENDUES " << rendered << '\n';
    std::cout << "PERDUES " << lost << '\n';
    std::cout << "ERREURS " << errors << '\n';
    if (firstWaitRefusal == 0) {
        std::cout << "PREMIER REFUS AUCUN\n";
    } else {
        std::cout << "PREMIER REFUS " << firstWaitRefusal << '\n';
    }
}
