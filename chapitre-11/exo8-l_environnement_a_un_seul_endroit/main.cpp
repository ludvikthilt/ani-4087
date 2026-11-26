#include <iostream>
#include <string>

long long readInteger(const std::string &text, std::size_t &pos) {
    while (pos < text.size() &&
           (text[pos] == ' ' || text[pos] == '\t' ||
            text[pos] == ',')) {
        ++pos;
    }
    long long sign = 1;
    if (pos < text.size() &&
        (text[pos] == '+' || text[pos] == '-')) {
        if (text[pos] == '-') {
            sign = -1;
        }
        ++pos;
    }
    long long value = 0;
    bool hasDigit = false;
    while (pos < text.size() &&
           text[pos] >= '0' && text[pos] <= '9') {
        hasDigit = true;
        value = value * 10 + (text[pos] - '0');
        ++pos;
    }
    return hasDigit ? sign * value : 0;
}

bool switchOn(const std::string &value) {
    if (value == "false") {
        return false;
    }
    if (!value.empty() && value[0] == '0') {
        return false;
    }
    return true;
}

int main() {
    std::string backend;
    long long hz = 0;
    std::string half;
    std::string depth;
    std::string list;
    std::string loader;
    long long latency = 0;

    std::string initial;
    std::getline(std::cin, initial);
    if (!initial.empty()) {
        std::size_t pos = 0;
        auto next = [&]() {
            while (pos < initial.size() &&
                   initial[pos] == ' ') {
                ++pos;
            }
            const std::size_t start = pos;
            while (pos < initial.size() &&
                   initial[pos] != ' ') {
                ++pos;
            }
            return initial.substr(start, pos - start);
        };
        backend = next();
        hz = std::stoll(next());
        half = next();
        depth = next();
        list = next();
        loader = next();
        latency = std::stoll(next());
    }

    std::string poseMode;
    std::cin >> poseMode;
    long long fixedPose[5] = {0, 0, 0, 1700, 0};
    if (poseMode == "FIXE") {
        for (long long &value : fixedPose) {
            std::cin >> value;
        }
    }

    int ignored = 0;
    int applied = 0;
    int variableCount = 0;
    std::cin >> variableCount;
    std::cin.ignore();
    std::string pose = "LIBRE";
    long long poseValues[5] = {};

    for (int i = 0; i < variableCount; ++i) {
        std::string entry;
        std::getline(std::cin, entry);
        const std::size_t equal = entry.find('=');
        if (equal == std::string::npos) {
            ++ignored;
            continue;
        }
        const std::string name = entry.substr(0, equal);
        const std::string value = entry.substr(equal + 1);
        bool recognized = false;
        if (name == "NK_XR_BACKEND") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else if (value == "openxr") {
                backend = "OPENXR";
                ++applied;
            } else {
                ++ignored;
            }
        } else if (name == "NK_XR_HZ") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                std::size_t pos = 0;
                hz = readInteger(value, pos);
                ++applied;
            }
        } else if (name == "NK_XR_HALF_RATE") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                half = switchOn(value) ? "OUI" : "NON";
                ++applied;
            }
        } else if (name == "NK_XR_DEPTH_LAYER") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                depth = switchOn(value) ? "OUI" : "NON";
                ++applied;
            }
        } else if (name == "NK_XR_LIST_EXT") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                list = switchOn(value) ? "OUI" : "NON";
                ++applied;
            }
        } else if (name == "NK_XR_OPENXR_LOADER") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                loader = value;
                ++applied;
            }
        } else if (name == "NK_XR_SIM_LATENCY_MS") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                std::size_t pos = 0;
                latency = readInteger(value, pos);
                ++applied;
            }
        } else if (name == "NK_XR_SIM_POSE") {
            recognized = true;
            if (value.empty()) {
                ++ignored;
            } else {
                std::size_t pos = 0;
                int count = 0;
                while (count < 5) {
                    while (pos < value.size() &&
                           (value[pos] == ',' || value[pos] == ' ')) {
                        ++pos;
                    }
                    if (pos >= value.size()) {
                        break;
                    }
                    const std::size_t before = pos;
                    poseValues[count] = readInteger(value, pos);
                    bool hadDigit = pos > before;
                    if (!hadDigit) {
                        break;
                    }
                    ++count;
                    if (pos >= value.size()) {
                        break;
                    }
                }
                if (count == 5) {
                    pose = "FIXE";
                    ++applied;
                } else {
                    ++ignored;
                }
            }
        }
        if (!recognized) {
            ++ignored;
        }
    }

    std::cout << "BACKEND " << backend << '\n';
    std::cout << "HZ " << hz << '\n';
    std::cout << "DEMI " << half << '\n';
    std::cout << "PROFONDEUR " << depth << '\n';
    std::cout << "LISTE " << list << '\n';
    std::cout << "LOADER " << (loader.empty() ? "-" : loader) << '\n';
    std::cout << "LATENCE " << latency << '\n';
    if (pose == "FIXE") {
        std::cout << "POSE FIXE";
        for (long long value : poseValues) {
            std::cout << ' ' << value;
        }
        std::cout << '\n';
    } else if (poseMode == "FIXE") {
        std::cout << "POSE FIXE";
        for (long long value : fixedPose) {
            std::cout << ' ' << value;
        }
        std::cout << '\n';
    } else {
        std::cout << "POSE " << poseMode << '\n';
    }
    std::cout << "APPLIQUEES " << applied << '\n';
    std::cout << "IGNOREES " << ignored << '\n';
}
