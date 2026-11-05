#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

int main() {
  std::uint64_t n, N;
  std::cin >> n >> N;

  std::vector<std::uint64_t> emplacements(n, 0);
  std::set<std::uint64_t> textures;
  std::uint64_t mortes = 0, larges = 0;

  for (std::uint64_t ordreNo = 0; ordreNo < N; ++ordreNo) {
    std::string ordre;
    std::cin >> ordre;
    if (ordre == "cree") {
      std::uint64_t h;
      std::cin >> h;
      textures.insert(h);
    } else if (ordre == "detruit") {
      std::uint64_t h;
      std::cin >> h;
      textures.erase(h);
    } else if (ordre == "set") {
      std::uint64_t i, h;
      std::cin >> i >> h;
      if (i >= n) {
        std::cout << "SET IGNORE " << i << '\n';
      } else {
        emplacements[i] = h;
        if (h > std::numeric_limits<std::uint32_t>::max())
          ++larges;
      }
    } else if (ordre == "get") {
      std::uint64_t i;
      std::cin >> i;
      const std::uint64_t h = i < n ? emplacements[i] : 0;
      if (h == 0) {
        std::cout << "GET " << i << " 0 VIDE\n";
      } else if (textures.count(h) != 0) {
        std::cout << "GET " << i << ' ' << h << " VIVANTE\n";
      } else {
        std::cout << "GET " << i << ' ' << h << " MORTE\n";
        ++mortes;
      }
    }
  }

  std::cout << "MORTES " << mortes << '\n';
  std::cout << "LARGES " << larges << '\n';
  return 0;
}
