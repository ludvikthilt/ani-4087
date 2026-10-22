#include <iomanip>
#include <iostream>

// Symptôme : le lacet continue à changer souris immobile.
// Cause : un delta d'événement est relu à chaque image au lieu d'être consommé.
// Preuve : les trois colonnes divergent sur les mêmes événements d'entrée.
// Correction : additionner les événements, consommer une fois, puis vider le
// cumul.
int main() {
  constexpr double degresParPixel = 0.1;
  double temps, brut;
  int nouvelEvenement;
  double lacetLu = 0.0, lacetVide = 0.0, lacetSansVidage = 0.0;
  double cumul = 0.0, cumulJamaisVide = 0.0;
  std::cout << "Saisir t(s), dernier delta brut, nouvel evenement (1/0); EOF "
               "termine.\n";
  while (std::cin >> temps >> brut >> nouvelEvenement) {
    if (nouvelEvenement) {
      cumul += brut;
      cumulJamaisVide += brut;
    }
    lacetLu += brut * degresParPixel;
    lacetVide += cumul * degresParPixel;
    lacetSansVidage += cumulJamaisVide * degresParPixel;
    std::cout << std::fixed << std::setprecision(4) << "t = " << temps
              << std::setprecision(3) << ", lu = " << lacetLu
              << ", vide = " << lacetVide
              << ", sans vidage = " << lacetSansVidage << '\n';
    cumul = 0.0; // Consommation unique par frame; l'accumulateur persistant
                 // reste faux.
  }
  return 0;
}
