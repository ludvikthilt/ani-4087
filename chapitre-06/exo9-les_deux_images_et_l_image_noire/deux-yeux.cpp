#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct Stats {
  std::size_t pixels = 0;
  unsigned maximum = 0;
  std::vector<std::uint8_t> diff;
};
static Stats compare(const std::vector<std::uint8_t> &a,
                     const std::vector<std::uint8_t> &b) {
  Stats s;
  if (a.size() != b.size() || a.size() % 4)
    return s;
  s.diff.resize(a.size());
  for (std::size_t p = 0; p < a.size(); p += 4) {
    unsigned d = 0;
    for (int c = 0; c < 4; ++c)
      d = std::max(d, unsigned(std::abs(int(a[p + c]) - int(b[p + c]))));
    s.maximum = std::max(s.maximum, d);
    if (d > 1)
      ++s.pixels;
    for (int c = 0; c < 4; ++c)
      s.diff[p + c] = static_cast<std::uint8_t>(
          std::min(255, 4 * std::abs(int(a[p + c]) - int(b[p + c]))));
  }
  return s;
}
int main() {
  constexpr int w = 640, h = 720;
  std::cout
      << "Outil d'analyse RGBA: " << w << "x" << h
      << " par oeil (1 843 200 octets).\n"
      << "Le rendu Salle/capture a fournir les deux buffers dans la meme "
         "frame.\n"
      << "difference.png et les captures oeil-gauche.png/oeil-droit.png "
         "doivent etre "
      << "enregistrees par le backend de rendu; pas d'images fictives creees.\n"
      << "La fonction compare compte les pixels dont le canal maximal differe "
         "de >1; "
      << "image diff: min(255,4*|difference|), RGBA.\n";
  // Appeler compare(gaucheRGBA,droiteRGBA) apres les captures.
  return 0;
}
