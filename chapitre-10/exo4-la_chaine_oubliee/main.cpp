#include <iostream>
#include <string>

int main() {
    int imageCount = 0;
    int callCount = 0;
    if (!(std::cin >> imageCount >> callCount)) {
        return 0;
    }

    int nextLeft = 0;
    int nextRight = 0;
    bool acquiredLeft = false;
    bool acquiredRight = false;
    bool frameOpen = false;
    int journal = 0;
    int warnings = 0;
    int silent = 0;

    for (int call = 1; call <= callCount; ++call) {
        std::string operation;
        std::cin >> operation;
        std::string response;

        if (operation == "wait") {
            if (frameOpen) {
                response = "REFUSE";
                ++journal;
            } else {
                response = "OK";
            }
        } else if (operation == "begin") {
            if (frameOpen) {
                response = "REFUSE";
                ++journal;
            } else {
                frameOpen = true;
                response = "OK";
            }
        } else if (operation == "acquire") {
            char eye = '\0';
            std::cin >> eye;
            bool &acquired = eye == 'G' ? acquiredLeft : acquiredRight;
            int nextImage = eye == 'G' ? nextLeft : nextRight;
            if (acquired) {
                response = "REFUSE";
                ++silent;
            } else {
                acquired = true;
                response = "OK " + std::to_string(nextImage);
            }
        } else if (operation == "release") {
            char eye = '\0';
            std::cin >> eye;
            bool &acquired = eye == 'G' ? acquiredLeft : acquiredRight;
            int &nextImage = eye == 'G' ? nextLeft : nextRight;
            if (!acquired) {
                response = "REFUSE";
                ++silent;
            } else {
                acquired = false;
                nextImage = (nextImage + 1) % imageCount;
                response = "OK";
            }
        } else if (operation == "end") {
            std::string projection;
            std::cin >> projection;
            bool hasLeft = false;
            bool hasRight = false;
            const bool hasProjection = projection != "-";
            if (hasProjection) {
                std::string rightProjection;
                std::cin >> rightProjection;
                hasLeft = projection == "1";
                hasRight = rightProjection == "1";
            }

            if (!frameOpen) {
                response = "REFUSE AUCUNE";
                ++journal;
            } else {
                frameOpen = false;
                if (hasProjection && hasLeft && acquiredLeft) {
                    response = "REFUSE ACQUISE G";
                    ++journal;
                } else if (hasProjection && hasRight && acquiredRight) {
                    response = "REFUSE ACQUISE D";
                    ++journal;
                } else if (hasProjection) {
                    std::string missingEyes;
                    if (!hasLeft) {
                        missingEyes += 'G';
                        ++warnings;
                    }
                    if (!hasRight) {
                        missingEyes += 'D';
                        ++warnings;
                    }
                    response =
                        missingEyes.empty() ? "OK" : "OK AVERT " + missingEyes;
                } else {
                    response = "OK";
                }
            }
        } else {
            response = "REFUSE";
        }

        std::cout << call << ' ' << operation;
        std::cout << ' ' << response << '\n';
    }

    std::cout << "JOURNAL " << journal << '\n';
    std::cout << "AVERTISSEMENTS " << warnings << '\n';
    std::cout << "SILENCIEUX " << silent << '\n';
}
