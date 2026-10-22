#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

// Scenario deterministe: le dernier delta est reutilise a chaque image.
int main() {
  constexpr double degresParPixel = 0.1;
  constexpr double imagesParSeconde = 120.0;
  double t = 0.0, brut = 0.0, lacet = 0.0;
  double dernierTemps = 0.0, dernierBrut = 0.0;
  bool premiereMesure = true;
  std::vector<double> temps, lacets;
  std::cout << "Saisir t(s) et delta residuel en pixels/image; EOF termine.\n";
  while (std::cin >> t >> brut) {
    if (!std::isfinite(t) || !std::isfinite(brut) || t < dernierTemps) {
      std::cerr << "Erreur: temps non fini ou non croissant.\n";
      return 1;
    }
    const double intervalle = premiereMesure ? t : t - dernierTemps;
    const double deltaReutilise = premiereMesure ? brut : dernierBrut;
    lacet += intervalle * imagesParSeconde * deltaReutilise * degresParPixel;
    temps.push_back(t);
    lacets.push_back(lacet);
    std::cout << std::fixed << std::setprecision(1) << "t = " << t
              << " s, images = " << (t * imagesParSeconde)
              << ", brut = " << brut << ", lacet = " << lacet << " deg.\n";
    dernierTemps = t;
    dernierBrut = brut;
    premiereMesure = false;
  }
  if (temps.size() >= 2 && temps.back() > temps.front())
    std::cout << "Derive observee = "
              << (lacets.back() - lacets.front()) /
                     (temps.back() - temps.front())
              << " deg/s (scenario calcule).\n";
  return 0;
}
