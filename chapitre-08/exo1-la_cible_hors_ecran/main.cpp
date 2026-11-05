#include <iostream>
#include <string>
#include <vector>

struct Cible {
  long long largeur, hauteur;
};

int main() {
  long long L, H, N;
  std::size_t F;
  std::cin >> L >> H >> F >> N;

  bool offscreen = false;
  bool bloque = false;
  std::vector<Cible> cibles;
  std::vector<bool> tamponPris(F, false);
  std::size_t vers = 0; // 0 : la fenetre, k : la cible k
  long long zoneL = L, zoneH = H;
  std::size_t images = 0;
  std::size_t numero = 0;

  for (long long i = 0; i < N && !bloque; ++i) {
    std::string ordre;
    std::cin >> ordre;
    if (ordre == "allume") {
      std::string nom;
      std::cin >> nom;
      if (nom == "OFFSCREEN")
        offscreen = true;
    } else if (ordre == "cible") {
      long long w, h;
      std::cin >> w >> h;
      if (!offscreen) {
        std::cout << "CIBLE NULLE\n";
      } else {
        cibles.push_back({w, h});
        std::cout << "CIBLE " << cibles.size() << ' ' << w << ' ' << h << '\n';
      }
    } else if (ordre == "vers") {
      std::size_t k;
      std::cin >> k;
      if (k <= cibles.size())
        vers = k;
      else
        std::cout << "VERS REFUSE\n";
    } else if (ordre == "taille") {
      std::cin >> zoneL >> zoneH;
    } else if (ordre == "image") {
      ++numero;
      const std::size_t tampon = (numero - 1) % F;
      if (tamponPris[tampon]) {
        std::cout << "BLOQUE " << numero << '\n';
        bloque = true;
      } else if (vers == 0) {
        std::cout << "IMAGE " << numero << " FENETRE\n";
        ++images;
      } else {
        const Cible &c = cibles[vers - 1];
        std::cout << "IMAGE " << numero << " CIBLE " << vers << '\n';
        ++images;
        // Une zone plus grande que la cible ne se termine jamais.
        if (zoneL > c.largeur || zoneH > c.hauteur)
          tamponPris[tampon] = true;
      }
    }
  }

  std::cout << "IMAGES " << images << '\n';
  std::cout << "ETAT " << (bloque ? "BLOQUE" : "LIBRE") << '\n';
  return 0;
}
