#include <cstdint>
#include <iostream>
#include <string>

int main() {
  long long N;
  std::cin >> N;

  std::uint64_t suivante = 101, courante = 0, index0 = 0;
  long long numero = 0, affichees = 0, noires = 0, perimees = 0;

  for (long long i = 0; i < N; ++i) {
    std::string ordre;
    std::cin >> ordre;
    if (ordre == "cible") {
      long long w, h;
      std::cin >> w >> h;
      courante = suivante++;
      std::cout << "CIBLE " << courante << ' ' << w << ' ' << h << '\n';
    } else if (ordre == "chaine") {
      index0 = 0;
    } else if (ordre == "enregistre") {
      index0 = courante;
    } else if (ordre == "image") {
      ++numero;
      if (index0 == 0) {
        std::cout << "IMAGE " << numero << " NOIR\n";
        ++noires;
      } else if (index0 == courante) {
        std::cout << "IMAGE " << numero << " AFFICHE " << index0 << '\n';
        ++affichees;
      } else {
        std::cout << "IMAGE " << numero << " PERIMEE " << index0 << '\n';
        ++perimees;
      }
    }
  }

  std::cout << "AFFICHEES " << affichees << '\n';
  std::cout << "NOIRES " << noires << '\n';
  std::cout << "PERIMEES " << perimees << '\n';
  return 0;
}
