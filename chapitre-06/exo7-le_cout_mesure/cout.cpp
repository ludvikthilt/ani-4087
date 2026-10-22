#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

struct Q {
  double w, x, y, z;
};
struct M {
  double a[3][3]{};
};
Q mul(Q a, Q b) {
  return {a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
          a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
          a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
          a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
}
Q norm(Q q) {
  double n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
  return {q.w / n, q.x / n, q.y / n, q.z / n};
}
M matrixYX(double y, double x) {
  double cy = cos(y), sy = sin(y), cx = cos(x), sx = sin(x);
  return {{{cy, sy * sx, sy * cx}, {0, cx, -sx}, {-sy, cy * sx, cy * cx}}};
}
Q fromMatrix(const M &m) {
  Q q{};
  double tr = m.a[0][0] + m.a[1][1] + m.a[2][2];
  if (tr > 0) {
    double s = sqrt(tr + 1) * 2;
    q = {s / 4, (m.a[2][1] - m.a[1][2]) / s, (m.a[0][2] - m.a[2][0]) / s,
         (m.a[1][0] - m.a[0][1]) / s};
  } else {
    q = {1, 0, 0, 0};
  }
  return q;
}
Q direct(double y, double x) {
  return norm(
      mul({cos(y / 2), 0, sin(y / 2), 0}, {cos(x / 2), sin(x / 2), 0, 0}));
}
int main(int argc, char **argv) {
  const std::string config = argc > 1 ? argv[1] : "Debug";
  constexpr int n = 1000000;
  constexpr double y = .7853981633974483, x = .5235987755982988;
  Q qa = direct(y, x), qb = norm(fromMatrix(matrixYX(y, x)));
  if (std::abs(std::abs(qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z) -
               1) > 1e-6) {
    std::cerr << "Echec d'equivalence\n";
    return 1;
  }
  volatile double somme = 0;
  std::cout << config << ", iterations = " << n
            << ", budget image 90 Hz = 11 ms\n";
  for (int algo = 0; algo < 2; ++algo)
    for (int run = 1; run <= 3; ++run) {
      auto debut = std::chrono::steady_clock::now();
      for (int i = 0; i < n; ++i) {
        double a = y + (i % 100) * 1e-5, b = x + (i % 70) * 1e-5;
        Q q = algo ? direct(a, b) : norm(fromMatrix(matrixYX(a, b)));
        somme = somme + q.w + q.x + q.y + q.z;
      }
      const double ms = std::chrono::duration<double, std::milli>(
                            std::chrono::steady_clock::now() - debut)
                            .count();
      std::cout << (algo ? "quaternions" : "matrices") << " run " << run << ": "
                << std::fixed << std::setprecision(3) << ms
                << " ms; somme=" << somme << '\n';
    }
}
