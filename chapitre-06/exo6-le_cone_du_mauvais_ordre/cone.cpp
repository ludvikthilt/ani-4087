#include <cmath>
#include <iomanip>
#include <iostream>

constexpr double pi = 3.14159265358979323846;
struct V {
  double x, y, z;
};
struct Q {
  double w, x, y, z;
};
Q operator*(Q a, Q b) {
  return {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
          a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
          a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
          a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
}
Q yaw(double a) { return {std::cos(a / 2), 0, std::sin(a / 2), 0}; }
Q pitch(double a) { return {std::cos(a / 2), std::sin(a / 2), 0, 0}; }
V turn(Q q, V v) {
  Q p{0, v.x, v.y, v.z}, c{q.w, -q.x, -q.y, -q.z};
  Q r = q * p * c;
  return {r.x, r.y, r.z};
}
int main() {
  std::cout << std::fixed << std::setprecision(2);
  for (int deg = 0; deg <= 180; deg += 45) {
    const double a = deg * pi / 180, p = 30 * pi / 180;
    const V f{0, 0, -1};
    const V good = turn(yaw(a) * pitch(p), f), bad = turn(pitch(p) * yaw(a), f);
    std::cout << "yaw = " << deg
              << " deg, bon hauteur = " << std::asin(good.y) * 180 / pi
              << " deg, mauvais hauteur = " << std::asin(bad.y) * 180 / pi
              << " deg\n";
  }
  std::cout << "Captures PNG: a realiser depuis la fenetre Salle; aucune image "
               "n'est fabriquee ici.\n";
}
