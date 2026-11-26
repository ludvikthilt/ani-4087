#include <iostream>
#include <cctype>
#include <string>
#include <unordered_set>
#include <vector>

bool wholeName(const std::string &text, const std::string &name) {
    std::size_t pos = 0;
    while ((pos = text.find(name, pos)) != std::string::npos) {
        bool leftOk = pos == 0;
        if (!leftOk) {
            const unsigned char c =
                static_cast<unsigned char>(text[pos - 1]);
            leftOk = !(std::isalnum(c) != 0 || text[pos - 1] == '_');
        }
        const std::size_t end = pos + name.size();
        bool rightOk = end == text.size();
        if (!rightOk) {
            const unsigned char c = static_cast<unsigned char>(text[end]);
            rightOk = !(std::isalnum(c) != 0 || text[end] == '_');
        }
        if (leftOk && rightOk) {
            return true;
        }
        pos = end;
    }
    return false;
}

int main() {
    std::unordered_set<std::string> decisions;
    std::unordered_set<std::string> definitions;
    char kind = '\0';
    int count = 0;

    std::cin >> kind >> count;
    for (int i = 0; i < count; ++i) {
        std::string name;
        std::cin >> name;
        if (kind == 'C') {
            decisions.insert(name);
        } else if (kind == 'D') {
            definitions.insert(name);
        }
    }
    if (!(std::cin >> kind >> count)) {
        std::cout << "ABSTRACTION TENUE\n";
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        std::string name;
        std::cin >> name;
        if (kind == 'C') {
            decisions.insert(name);
        } else if (kind == 'D') {
            definitions.insert(name);
        }
    }

    int lineCount = 0;
    if (!(std::cin >> lineCount)) {
        std::cout << "DECISIONS 0\nFUITES 0\nDEFINIS 0\nABSTRACTION TENUE\n";
        return 0;
    }

    int decisionCount = 0;
    int leakCount = 0;
    int definitionCount = 0;
    for (int i = 1; i <= lineCount; ++i) {
        std::string zone;
        std::cin >> zone;
        std::string text;
        std::getline(std::cin, text);
        std::size_t first = 0;
        while (first < text.size() &&
               (text[first] == ' ' || text[first] == '\t')) {
            ++first;
        }
        if (text.substr(first, 2) == "//") {
            continue;
        }

        bool inDecision = false;
        for (const std::string &name : decisions) {
            if (wholeName(text, name)) {
                inDecision = true;
                break;
            }
        }
        bool isLeak = false;
        if (inDecision) {
            if (zone == "INIT") {
                ++decisionCount;
            } else if (zone == "BOUCLE" || zone == "SCENE") {
                isLeak = true;
            }
        }

        bool isDefined = false;
        if (zone != "FABRIQUE") {
            for (const std::string &name : definitions) {
                if (wholeName(text, name)) {
                    isDefined = true;
                    break;
                }
            }
        }

        if (isLeak) {
            std::cout << "FUITE " << i << ' ' << zone << '\n';
            ++leakCount;
        }
        if (isDefined) {
            std::cout << "DEFINI " << i << ' ' << zone << '\n';
            ++definitionCount;
        }
    }

    std::cout << "DECISIONS " << decisionCount << '\n';
    std::cout << "FUITES " << leakCount << '\n';
    std::cout << "DEFINIS " << definitionCount << '\n';
    std::cout << (leakCount == 0 && definitionCount == 0
                      ? "ABSTRACTION TENUE\n"
                      : "ABSTRACTION FUIT\n");
}
