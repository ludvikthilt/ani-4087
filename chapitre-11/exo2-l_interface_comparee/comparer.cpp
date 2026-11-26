#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  int countA = 0;
  std::cin >> countA;
  std::vector<std::string> a(static_cast<std::size_t>(countA));
  for (std::string &name : a) {
    std::cin >> name;
  }

  int countB = 0;
  std::cin >> countB;
  std::vector<std::string> b(static_cast<std::size_t>(countB));
  std::unordered_set<std::string> setA;
  for (std::string &name : b) {
    std::cin >> name;
  }
  for (const std::string &name : a) {
    setA.insert(name);
  }
  std::unordered_set<std::string> setB;
  for (const std::string &name : b) {
    setB.insert(name);
  }

  int common = 0;
  for (const std::string &name : setA) {
    if (setB.count(name) != 0) {
      ++common;
    }
  }
  std::cout << "DEUX " << common << '\n';
  for (const std::string &name : a) {
    if (setB.count(name) == 0) {
      std::cout << "SEUL_A " << name << '\n';
    }
  }
  for (const std::string &name : b) {
    if (setA.count(name) == 0) {
      std::cout << "SEUL_B " << name << '\n';
    }
  }

  std::unordered_set<std::string> unionSet = setA;
  unionSet.insert(setB.begin(), setB.end());
  int different = 0;
  for (const std::string &name : unionSet) {
    if (setA.count(name) != setB.count(name)) {
      ++different;
    }
  }
  std::cout << "DIFFERENTES " << different << " SUR " << unionSet.size()
            << '\n';
}
