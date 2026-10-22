#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

struct V3 {
  double x, y, z;
};
struct Tete {
  double yaw, pitch; // radians
  V3 position;
  V3 Regard() const {
    return {-std::sin(yaw) * std::cos(pitch), std::sin(pitch),
            -std::cos(yaw) * std::cos(pitch)};
  }
};

static bool proche(double a, double b) { return std::abs(a - b) < 1e-6; }
static bool essai(const char *nom, double yawDeg, double pitchDeg, V3 attendu) {
  constexpr double pi = 3.14159265358979323846;
  const Tete t{yawDeg * pi / 180.0, pitchDeg * pi / 180.0, {0, 0, 0}};
  const V3 obtenu = t.Regard();
  const bool ok = proche(obtenu.x, attendu.x) && proche(obtenu.y, attendu.y) &&
                  proche(obtenu.z, attendu.z);
  std::cout << std::fixed << std::setprecision(1) << nom << " attendu ("
            << attendu.x << ", " << attendu.y << ", " << attendu.z
            << ") obtenu (" << obtenu.x << ", " << obtenu.y << ", " << obtenu.z
            << ") " << (ok ? "OK" : "ECHEC") << '\n';
  return ok;
}
int main() {
  if (!std::getenv("MASALLE_TEST")) {
    std::cout << "Definir MASALLE_TEST=1 pour lancer les tests avant toute "
                 "fenetre.\n";
    return 0;
  }
  const bool ok = essai("neutre", 0, 0, {0, 0, -1}) &
                  essai("yaw 90", 90, 0, {-1, 0, 0}) &
                  essai("pitch 30", 0, 30, {0, 0.5, -0.8660254});
  return ok ? 0 : 1;
}
