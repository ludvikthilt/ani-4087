#include <iostream>
#include <string>

int main() {
    int machineCount = 0;
    std::cin >> machineCount;
    std::cin.ignore();
    for (int i = 1; i <= machineCount; ++i) {
        std::string registry;
        std::getline(std::cin, registry);
        if (registry == "-") {
            std::cout << i << " REGISTRE AUCUN\n";
            int ignoredLines = 0;
            std::cin >> ignoredLines;
            std::cin.ignore();
            continue;
        }

        std::cout << i << " MANIFESTE " << registry << '\n';
        int lineCount = 0;
        std::cin >> lineCount;
        std::cin.ignore();
        if (lineCount == -1) {
            std::cout << i << " ECHEC ILLISIBLE\n";
            continue;
        }

        std::string manifest;
        manifest.reserve(static_cast<std::size_t>(lineCount) * 40);
        for (int line = 0; line < lineCount; ++line) {
            std::string text;
            std::getline(std::cin, text);
            manifest += text;
            manifest += '\n';
        }

        const std::string key = "\"library_path\"";
        const std::size_t keyPos = manifest.find(key);
        if (keyPos == std::string::npos) {
            std::cout << i << " ECHEC CLE\n";
            continue;
        }
        const std::size_t colonPos = manifest.find(':', keyPos + key.size());
        if (colonPos == std::string::npos) {
            std::cout << i << " ECHEC DEUX_POINTS\n";
            continue;
        }
        const std::size_t firstQuote = manifest.find('"', colonPos + 1);
        if (firstQuote == std::string::npos) {
            std::cout << i << " ECHEC GUILLEMET\n";
            continue;
        }
        const std::size_t secondQuote = manifest.find('"', firstQuote + 1);
        if (secondQuote == std::string::npos) {
            std::cout << i << " ECHEC GUILLEMET\n";
            continue;
        }

        std::string value;
        for (std::size_t pos = firstQuote + 1; pos < secondQuote; ++pos) {
            if (manifest[pos] == '\\' && pos + 1 < secondQuote &&
                manifest[pos + 1] == '\\') {
                continue;
            }
            value += manifest[pos];
        }
        if (value.empty()) {
            std::cout << i << " ECHEC VIDE\n";
            continue;
        }

        std::cout << i << " VALEUR " << value << '\n';
        bool absolute =
            (value.size() >= 2 && value[1] == ':') ||
            value[0] == '\\' || value[0] == '/';
        if (absolute) {
            std::cout << i << " ABSOLU\n";
            std::cout << i << " CHARGE " << value << '\n';
        } else {
            std::cout << i << " RELATIF\n";
            std::size_t separator = registry.find_last_of("\\/");
            std::string directory = registry.substr(0, separator + 1);
            std::cout << i << " CHARGE " << directory << value << '\n';
        }
    }
}
