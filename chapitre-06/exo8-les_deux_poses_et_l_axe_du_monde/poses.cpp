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
Q rot(double a, int axis) {
  double s = sin(a / 2), c = cos(a / 2);
  return axis == 0 ? Q{c, s, 0, 0} : axis == 1 ? Q{c, 0, s, 0} : Q{c, 0, 0, s};
}
V apply(Q q, V v) {
  Q p{0, v.x, v.y, v.z}, c{q.w, -q.x, -q.y, -q.z};
  Q r = q * p * c;
  return {r.x, r.y, r.z};
}
V add(V a, V b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
V scale(V a, double s) { return {a.x * s, a.y * s, a.z * s}; }
void show(const char *n, V v) {
  std::cout << n << " (" << std::fixed << std::setprecision(4) << v.x << ", "
            << v.y << ", " << v.z << ") m\n";
}
int main() {
  const V h{.30, 1.70, 1.20}, worldX{1, 0, 0};
  constexpr double half = .063 / 2;
  const Q poses[] = {Q{1, 0, 0, 0}, rot(30 * pi / 180, 2),
                     rot(90 * pi / 180, 1)};
  const char *names[] = {"neutre", "roll 30", "yaw 90"};
  for (int i = 0; i < 3; ++i) {
    const V right = apply(
        poses[i], {-1, 0, 0}); // NkQuat::Right() in the local header is -X.
    V leftH = add(h, scale(right, half)), rightH = add(h, scale(right, -half));
    V leftW = add(h, scale(worldX, half)),
      rightW = add(h, scale(worldX, -half));
    std::cout << names[i] << '\n';
    show("  local gauche", leftH);
    show("  local droit", rightH);
    show("  monde gauche", leftW);
    show("  monde droit", rightW);
    std::cout << "  ecart oeil gauche = " << std::fixed << std::setprecision(2)
              << std::hypot(std::hypot(leftH.x - leftW.x, leftH.y - leftW.y),
                            leftH.z - leftW.z) *
                     1000
              << " mm\n";
  }
}
