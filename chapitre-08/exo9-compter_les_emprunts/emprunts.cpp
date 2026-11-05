#include <iostream>
#include <string>

struct Chaine {
  unsigned images;
  unsigned prochaine = 0;
  bool emprunt = false;
  long long reussies = 0, refusees = 0, liberations = 0;

  bool Acquire() {
    if (emprunt) {
      ++refusees;
      return false;
    }
    emprunt = true;
    ++reussies;
    return true;
  }
  void Release() {
    prochaine = (prochaine + 1) % images;
    emprunt = false;
    ++liberations;
  }
};

int main() {
  unsigned n;
  long long N;
  std::cin >> n >> N;

  Chaine chaine{n};
  long long premiereFuite = 0;

  for (long long t = 1; t <= N; ++t) {
    std::string trame;
    std::cin >> trame;

    if (!chaine.Acquire()) {
      std::cout << t << " BLOQUEE\n";
      continue;
    }
    if (trame == "normal") {
      chaine.Release();
      std::cout << t << " OK\n";
    } else if (trame == "sortie") {
      // Le chemin qui fuit : on sort sans rendre l'image.
      if (premiereFuite == 0)
        premiereFuite = t;
      std::cout << t << " FUITE\n";
    } else if (trame == "double") {
      chaine.Acquire();
      chaine.Release();
      std::cout << t << " DOUBLE\n";
    }
  }

  std::cout << "REUSSIES " << chaine.reussies << '\n';
  std::cout << "REFUSEES " << chaine.refusees << '\n';
  std::cout << "LIBERATIONS " << chaine.liberations << '\n';
  std::cout << "ECART " << chaine.reussies - chaine.liberations << '\n';
  if (premiereFuite != 0)
    std::cout << "PREMIERE FUITE " << premiereFuite << '\n';
  else
    std::cout << "PREMIERE FUITE AUCUNE\n";
  return 0;
}
