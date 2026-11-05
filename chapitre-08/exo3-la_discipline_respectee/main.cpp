#include <iostream>
#include <string>

int main() {
  unsigned n;
  long long N;
  std::cin >> n >> N;

  unsigned prochaine = 0, empruntee = 0;
  bool emprunt = false, dessinee = false;
  bool aSoumettre = false, renduVide = false;
  long long soumises = 0, refus = 0, horsEmprunt = 0;

  for (long long i = 0; i < N; ++i) {
    std::string ordre;
    std::cin >> ordre;
    if (ordre == "acquire") {
      if (emprunt) {
        std::cout << "ACQUIRE REFUSE\n";
        ++refus;
      } else {
        emprunt = true;
        dessinee = false;
        empruntee = prochaine;
        std::cout << "ACQUIRE " << empruntee << '\n';
      }
    } else if (ordre == "draw") {
      if (emprunt) {
        dessinee = true;
        std::cout << "DRAW " << empruntee << '\n';
      } else {
        std::cout << "DRAW HORS EMPRUNT\n";
        ++horsEmprunt;
      }
    } else if (ordre == "release") {
      if (!emprunt) {
        std::cout << "RELEASE REFUSE\n";
        ++refus;
      } else {
        prochaine = (prochaine + 1) % n;
        emprunt = false;
        aSoumettre = true;
        renduVide = !dessinee;
        std::cout << "RELEASE OK\n";
      }
    } else if (ordre == "submit") {
      if (emprunt) {
        std::cout << "SUBMIT REFUSE EMPRUNTEE\n";
        ++refus;
      } else if (!aSoumettre) {
        std::cout << "SUBMIT REFUSE RIEN\n";
        ++refus;
      } else {
        const unsigned j = (prochaine + n - 1) % n;
        std::cout << "SUBMIT " << j << (renduVide ? " VIDE" : "") << '\n';
        aSoumettre = false;
        ++soumises;
      }
    }
  }

  std::cout << "SOUMISES " << soumises << '\n';
  std::cout << "REFUS " << refus << '\n';
  std::cout << "HORS EMPRUNT " << horsEmprunt << '\n';
  return 0;
}
