#include <iostream>
#include <string>

int main() {
  unsigned n;
  std::string v; // gardee telle quelle : elle peut depasser un int
  long long N;
  std::cin >> n >> v >> N;

  std::string variables[26];
  for (std::string &variable : variables)
    variable = v;
  unsigned prochaine = 0;
  bool emprunt = false;

  for (long long i = 0; i < N; ++i) {
    std::string ordre;
    std::cin >> ordre;
    if (ordre == "acquire") {
      char x;
      std::cin >> x;
      std::string &variable = variables[x - 'a'];
      const bool reussi = !emprunt;
      if (reussi) {
        variable = std::to_string(prochaine);
        emprunt = true;
      }
      std::cout << "ACQUIRE " << (reussi ? "VRAI " : "FAUX ") << x << ' '
                << variable << '\n';
    } else if (ordre == "release") {
      if (emprunt) {
        prochaine = (prochaine + 1) % n;
        emprunt = false;
        std::cout << "RELEASE VRAI\n";
      } else {
        std::cout << "RELEASE FAUX\n";
      }
    } else if (ordre == "last") {
      std::cout << "LAST " << (prochaine + n - 1) % n << '\n';
    }
  }

  std::cout << "EMPRUNTEE " << (emprunt ? "OUI" : "NON") << '\n';
  std::cout << "PROCHAINE " << prochaine << '\n';
  return 0;
}
