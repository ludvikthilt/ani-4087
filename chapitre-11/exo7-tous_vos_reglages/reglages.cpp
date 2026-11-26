#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  int count = 0;
  std::cin >> count;
  std::vector<std::string> order;
  std::unordered_map<std::string, bool> hasGetenv;
  std::unordered_map<std::string, bool> hasRead;
  std::unordered_map<std::string, bool> hasWrite;
  std::unordered_map<std::string, bool> hasEnv;

  for (int i = 0; i < count; ++i) {
    std::string name;
    std::string action;
    std::cin >> name >> action;
    if (hasGetenv.count(name) == 0) {
      hasGetenv[name] = false;
      hasRead[name] = false;
      hasWrite[name] = false;
      hasEnv[name] = false;
      order.push_back(name);
    }
    if (action == "GETENV") {
      hasGetenv[name] = true;
    } else if (action == "LIT") {
      hasRead[name] = true;
    } else if (action == "ECRIT") {
      hasWrite[name] = true;
    } else if (action == "ENV") {
      hasEnv[name] = true;
    }
  }

  int menuCount = 0;
  for (const std::string &name : order) {
    std::string category;
    if (hasGetenv[name]) {
      category = "CACHE";
    } else if (!hasRead[name]) {
      category = "FANTOME";
    } else if (!hasWrite[name] && !hasEnv[name]) {
      category = "CONSTANTE";
    } else {
      category = "MENU";
      ++menuCount;
    }
    std::cout << name << ' ' << category << '\n';
  }
  std::cout << "MENU " << menuCount << " SUR " << order.size() << '\n';
}
