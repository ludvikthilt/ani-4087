#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  unsigned n;
  long long T, x0, v;
  std::string modes;
  std::cin >> n >> T >> x0 >> v >> modes;

  std::vector<long long> emplacements(n, 0);
  unsigned prochaine = 0;
  bool precedenteMontree = false, aSaute = false;
  long long precedente = 0, sautMin = 0, sautMax = 0;

  for (long long t = 1; t <= T; ++t) {
    const char mode = modes[t - 1];

    const unsigned empruntee = prochaine;
    emplacements[empruntee] = t;

    unsigned soumis = empruntee;
    if (mode == 'P')
      soumis = (prochaine + n - 1) % n;
    prochaine = (prochaine + 1) % n;
    if (mode == 'D')
      soumis = (prochaine + n - 1) % n;

    const long long f = emplacements[soumis];
    if (f == 0) {
      std::cout << t << " NOIR -\n";
      precedenteMontree = false;
      continue;
    }

    const long long position = x0 + v * f;
    if (precedenteMontree && t != 1) {
      const long long saut = position - precedente;
      std::cout << t << ' ' << position << ' ' << saut << '\n';
      sautMin = aSaute ? std::min(sautMin, saut) : saut;
      sautMax = aSaute ? std::max(sautMax, saut) : saut;
      aSaute = true;
    } else {
      std::cout << t << ' ' << position << " -\n";
    }
    precedente = position;
    precedenteMontree = true;
  }

  if (aSaute) {
    std::cout << "SAUT MIN " << sautMin << '\n';
    std::cout << "SAUT MAX " << sautMax << '\n';
    std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << '\n';
  } else {
    std::cout << "SAUTS AUCUN\n";
  }
  return 0;
}
