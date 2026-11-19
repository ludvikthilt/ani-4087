#include <iostream>
#include <string>

int main() {
    int imageCount = 0;
    if (!(std::cin >> imageCount)) {
        return 0;
    }

    int correct = 0;
    int faulty = 0;

    for (int image = 1; image <= imageCount; ++image) {
        int callCount = 0;
        std::cin >> callCount;

        bool waited = false;
        bool begun = false;
        bool locatedViews = false;
        bool acquiredLeft = false;
        bool acquiredRight = false;
        bool ended = false;
        std::string fault;
        int faultPosition = 0;

        for (int call = 1; call <= callCount; ++call) {
            std::string name;
            std::cin >> name;

            if (!fault.empty()) {
                continue;
            }

            if (ended) {
                fault = "APRES_END";
            } else if (name == "WAIT") {
                if (begun) {
                    fault = "WAIT_APRES_BEGIN";
                } else {
                    waited = true;
                }
            } else if (name == "BEGIN") {
                if (!waited) {
                    fault = "BEGIN_SANS_WAIT";
                } else if (begun) {
                    fault = "DOUBLE_BEGIN";
                } else {
                    begun = true;
                }
            } else if (name == "VUES") {
                if (!waited) {
                    fault = "VUES_SANS_WAIT";
                } else {
                    locatedViews = true;
                }
            } else if (name == "PREND_G") {
                if (!begun) {
                    fault = "PREND_SANS_BEGIN";
                } else if (!locatedViews) {
                    fault = "PREND_SANS_VUES";
                } else if (acquiredLeft) {
                    fault = "DOUBLE_PREND";
                } else {
                    acquiredLeft = true;
                }
            } else if (name == "PREND_D") {
                if (!begun) {
                    fault = "PREND_SANS_BEGIN";
                } else if (!locatedViews) {
                    fault = "PREND_SANS_VUES";
                } else if (acquiredRight) {
                    fault = "DOUBLE_PREND";
                } else {
                    acquiredRight = true;
                }
            } else if (name == "LACHE_G") {
                if (!acquiredLeft) {
                    fault = "LACHE_SANS_PREND";
                } else {
                    acquiredLeft = false;
                }
            } else if (name == "LACHE_D") {
                if (!acquiredRight) {
                    fault = "LACHE_SANS_PREND";
                } else {
                    acquiredRight = false;
                }
            } else if (name == "END") {
                if (!begun) {
                    fault = "END_SANS_BEGIN";
                } else if (acquiredLeft || acquiredRight) {
                    fault = "END_IMAGE_PRISE";
                } else {
                    ended = true;
                }
            }

            if (!fault.empty()) {
                faultPosition = call;
            }
        }

        if (fault.empty() && !ended) {
            fault = "SANS_END";
            faultPosition = callCount + 1;
        }

        if (fault.empty()) {
            ++correct;
            std::cout << image << " OK\n";
        } else {
            ++faulty;
            std::cout << image << " FAUTE " << faultPosition << ' ' << fault
                      << '\n';
        }
    }

    std::cout << "JUSTES " << correct << '\n';
    std::cout << "FAUTIVES " << faulty << '\n';
}
