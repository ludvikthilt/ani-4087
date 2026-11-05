#include <cstdint>
#include <iostream>
#include <string>

int main() {
  std::uint64_t N;
  std::cin >> N;

  std::uint64_t acceptees = 0, occupes = 0, gauche = 0, droit = 0, sansNom = 0;

  for (std::uint64_t i = 0; i < N; ++i) {
    std::uint64_t largeur, hauteur, images;
    int oeil;
    std::string nom;
    std::cin >> largeur >> hauteur >> images >> oeil >> nom;

    const bool anonyme = nom == "-";
    const std::string affiche = anonyme ? "SANS-NOM" : nom;

    if (largeur == 0 || hauteur == 0) {
      std::cout << "REFUSEE " << affiche << " TAILLE\n";
    } else if (images == 0 || images > 4) {
      std::cout << "REFUSEE " << affiche << " IMAGES\n";
    } else {
      std::cout << "CHAINE " << affiche << ' ' << largeur << ' ' << hauteur
                << ' ' << images << ' ' << (oeil == 0 ? "GAUCHE" : "DROIT")
                << '\n';
      ++acceptees;
      occupes += images;
      if (oeil == 0)
        ++gauche;
      else
        ++droit;
      if (anonyme)
        ++sansNom;
    }
  }

  std::cout << "ACCEPTEES " << acceptees << '\n';
  std::cout << "EMPLACEMENTS " << 4 * acceptees << '\n';
  std::cout << "OCCUPES " << occupes << '\n';
  std::cout << "GAUCHE " << gauche << '\n';
  std::cout << "DROIT " << droit << '\n';
  std::cout << "SANS NOM " << sansNom << '\n';
  return 0;
}
