#include <iostream>
#include <string>

int main() {
    int machineCount = 0;
    if (!(std::cin >> machineCount)) {
        if (machineCount == 0) {
            std::cout << "AUCUNE MACHINE\n";
        }
        return 0;
    }
    if (machineCount == 0) {
        std::cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (int i = 1; i <= machineCount; ++i) {
        std::string demand;
        std::string variable;
        std::string loader;
        std::string registry;
        std::string link;
        std::string card;
        std::cin >> demand >> variable >> loader >> registry >> link >> card;

        int charged = 0;
        int freed = 0;
        bool hasEntry = false;
        std::string source;

        if (demand == "SIMULATEUR") {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        } else {
            if (variable != "-") {
                if (variable == "ABSENT") {
                    std::cout << i << " VARIABLE IGNOREE\n";
                } else {
                    std::cout << i << " VARIABLE CHARGEE\n";
                    ++charged;
                    if (variable == "BON") {
                        hasEntry = true;
                        source = "VARIABLE";
                    } else if (variable == "SANS") {
                        std::cout << i << " SANS_ENTREE\n";
                        ++freed;
                    }
                }
            }

            if (!hasEntry && charged == 0) {
                if (loader == "ABSENT") {
                    std::cout << i << " LOADER ABSENT\n";
                } else {
                    std::cout << i << " LOADER CHARGE\n";
                    ++charged;
                    if (loader == "BON") {
                        hasEntry = true;
                        source = "LOADER";
                    } else if (loader == "SANS") {
                        std::cout << i << " SANS_ENTREE\n";
                        ++freed;
                    }
                }
            }

            if (!hasEntry) {
                std::cout << i << " DIRECT " << registry << '\n';
                if (registry == "NEGO_KO" || registry == "BON") {
                    ++charged;
                    if (registry == "BON") {
                        hasEntry = true;
                        source = "DIRECT";
                    }
                }
            }

            if (!hasEntry) {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (charged > freed) {
                    ++freed;
                }
            } else {
                std::cout << i << " BACKEND OPENXR " << source << '\n';
                if (link == "NON") {
                    std::cout << i << " LIAISON ECHOUEE\n";
                    ++freed;
                }
            }
        }

        if (demand == "OPENXR" &&
            hasEntry && link == "OUI") {
            std::cout << i << " NIVEAU 1 CASQUE\n";
        } else if (card == "OUI") {
            std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        } else {
            std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        }
        std::cout << i << " CHARGEES " << charged << " LIBEREES " << freed
                  << '\n';
    }
}
