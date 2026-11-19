#include <iostream>
#include <string>
#include <vector>

int main() {
    int applicationCount = 0;
    if (!(std::cin >> applicationCount)) {
        return 0;
    }

    int silentWithSymptoms = 0;
    for (int application = 1; application <= applicationCount; ++application) {
        std::string endPolicy;
        int leftChain = 0;
        int rightChain = 0;
        char instant = '\0';
        char pose = '\0';
        char space = '\0';
        std::cin >> endPolicy >> leftChain >> rightChain >> instant >> pose >>
            space;

        std::vector<std::string> symptoms;
        if (endPolicy == "JAMAIS") {
            symptoms.emplace_back("FIGE");
        } else if (endPolicy == "SI_RENDU") {
            symptoms.emplace_back("NE_REPART_PAS");
        }
        if (leftChain == 0) {
            symptoms.emplace_back("OEIL_NOIR_G");
        }
        if (rightChain == 0) {
            symptoms.emplace_back("OEIL_NOIR_D");
        }
        if (instant == 'N') {
            symptoms.emplace_back("TREMBLE");
        }
        if (pose == 'F') {
            symptoms.emplace_back("DE_TRAVERS");
        }
        if (space == 'L') {
            symptoms.emplace_back("DECALE");
        }

        if (symptoms.empty()) {
            std::cout << application << " CASQUE AUCUN\n";
        } else {
            std::cout << application << " CASQUE";
            for (const std::string &symptom : symptoms) {
                std::cout << ' ' << symptom;
            }
            std::cout << '\n';
        }

        const bool simulatorSpeaks =
            endPolicy != "TOUJOURS" || leftChain == 0 || rightChain == 0;
        std::cout << application << " SIMULATEUR "
                  << (simulatorSpeaks ? "DIT" : "MUET") << '\n';
        if (!symptoms.empty() && !simulatorSpeaks) {
            ++silentWithSymptoms;
        }
    }

    std::cout << "MUETTES " << silentWithSymptoms << '\n';
}
