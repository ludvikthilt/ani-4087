#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

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
Q axis(double angle, bool y) {
  double s = std::sin(angle / 2), c = std::cos(angle / 2);
  return y ? Q{c, 0, s, 0} : Q{c, s, 0, 0};
}
V rotate(Q q, V v) {
  Q p{0, v.x, v.y, v.z}, c{q.w, -q.x, -q.y, -q.z};
  Q r = q * p * c;
  return {r.x, r.y, r.z};
}
V matrixYX(double y, double x,
           V v) { // NkMat4f::RotationY(yaw)*RotationX(pitch)
  V a{v.x, std::cos(x) * v.y - std::sin(x) * v.z,
      std::sin(x) * v.y + std::cos(x) * v.z};
  return {std::cos(y) * a.x + std::sin(y) * a.z, a.y,
          -std::sin(y) * a.x + std::cos(y) * a.z};
}
void print(const char *name, V v) {
  std::cout << std::fixed << std::setprecision(4) << name << ": (" << v.x
            << ", " << v.y << ", " << v.z << ")\n";
}
int main() {
  const double y = 45 * pi / 180, x = 30 * pi / 180;
  const V f{0, 0, -1};
  const Q yaw = axis(y, true), pitch = axis(x, false);
  print("qYaw*qPitch", rotate(yaw * pitch, f));
  print("qPitch*qYaw", rotate(pitch * yaw, f));
  print("RotationY*RotationX", matrixYX(y, x, f));
  std::cout
      << "Ordre a basculer (y = yaw*pitch, p = pitch*yaw, entree = fin):\n";
  std::string key;
  while (std::cin >> key && key != "fin") {
    print(key == "y" ? "selection yaw*pitch" : "selection pitch*yaw",
          rotate(key == "y" ? yaw * pitch : pitch * yaw, f));
  }
}
