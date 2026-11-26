// Commande: g++ -std=c++17 -Wall main.cpp -o programme
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::string countLine;
    if (!std::getline(std::cin, countLine)) {
        std::cout << "ENTETE 0\nIGNOREES 0\nVARIABLE AUCUNE\nPART 0\n";
        return 0;
    }
    int lineCount = 0;
    try {
        lineCount = std::stoi(countLine);
    } catch (...) {
        lineCount = 0;
    }

    std::vector<std::string> lines;
    lines.reserve(lineCount);
    for (int i = 0; i < lineCount; ++i) {
        std::string line;
        std::getline(std::cin, line);
        lines.push_back(line);
    }

    int headerCount = 0;
    std::unordered_set<std::string> seen;
    std::vector<std::string> variables;
    for (const std::string &line : lines) {
        std::size_t first = 0;
        while (first < line.size() &&
               (line[first] == ' ' || line[first] == '\t')) {
            ++first;
        }
        if (first == line.size() || line.substr(first, 2) != "//") {
            break;
        }
        ++headerCount;
        const std::string trimmed = line.substr(first);
        for (std::size_t i = 0; i < trimmed.size(); ++i) {
            if (trimmed.compare(i, 3, "NK_") == 0 &&
                (i == 0 || (!std::isalnum(static_cast<unsigned char>(trimmed[i - 1])) &&
                            trimmed[i - 1] != '_'))) {
                std::size_t end = i + 3;
                while (end < trimmed.size() &&
                       (std::isupper(static_cast<unsigned char>(trimmed[end])) ||
                        std::isdigit(static_cast<unsigned char>(trimmed[end])) ||
                        trimmed[end] == '_')) {
                    ++end;
                }
                if (end == i + 3 || end >= trimmed.size() ||
                    trimmed[end] != '=') {
                    continue;
                }
                const std::string name = trimmed.substr(i, end - i);
                if (seen.insert(name).second) {
                    variables.push_back(name);
                }
                i = end;
            }
        }
    }

    std::cout << "ENTETE " << headerCount << '\n';
    std::cout << "IGNOREES " << (lineCount - headerCount) << '\n';
    if (variables.empty()) {
        std::cout << "VARIABLE AUCUNE\n";
    } else {
        for (const std::string &name : variables) {
            std::cout << "VARIABLE " << name << '\n';
        }
    }
    const long long part =
        lineCount == 0 ? 0 : (100LL * headerCount) / lineCount;
    std::cout << "PART " << part << '\n';
}
