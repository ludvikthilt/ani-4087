#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

using Mat =
    std::array<std::array<double, 4>, 4>; // mat[col][row], comme NkMat4f.
constexpr double pi = 3.14159265358979323846;
Mat asym(double l, double r, double u, double d, double n, double f) {
  Mat m{};
  m[0][0] = 2 / (r - l);
  m[2][0] = (r + l) / (r - l);
  m[1][1] = 2 / (u - d);
  m[2][1] = (u + d) / (u - d);
  m[2][2] = -(f + n) / (f - n);
  m[3][2] = -2 * f * n / (f - n);
  m[2][3] = -1;
  return m;
}
Mat symmetric(double fovy, double aspect, double n, double f) {
  const double q = 1 / std::tan(fovy / 2);
  Mat m{};
  m[0][0] = q / aspect;
  m[1][1] = q;
  m[2][2] = -(f + n) / (f - n);
  m[3][2] = -2 * f * n / (f - n);
  m[2][3] = -1;
  return m;
}
void compare(const char *name, const Mat &a, const Mat &b) {
  double maximum = 0;
  std::cout << name << '\n';
  for (int row = 0; row < 4; ++row) {
    double rowmax = 0;
    for (int col = 0; col < 4; ++col)
      rowmax = std::max(rowmax, std::abs(a[col][row] - b[col][row]));
    maximum = std::max(maximum, rowmax);
    std::cout << "ligne " << row << ": ecart max = " << std::fixed
              << std::setprecision(6) << rowmax << '\n';
  }
  std::cout << "ecart maximal = " << maximum << '\n';
}
int main() {
  const double n = .05, f = 100;
  const double vertical = 70 * pi / 360;
  const double horizontal = std::atan(std::tan(vertical) * (1280.0 / 720.0));
  Mat manualSym = asym(-horizontal, horizontal, vertical, -vertical, n, f);
  Mat engineSym = symmetric(70 * pi / 180, 1280.0 / 720.0, n, f);
  compare("test 1: FOV symetrique 70 deg / aspect 1280:720", manualSym,
          engineSym);
  auto rad = [](double d) { return d * pi / 180; };
  Mat manualQuest =
      asym(tan(rad(-52)), tan(rad(45)), tan(rad(48)), tan(rad(-50)), n, f);
  // Equivalent analytic form of SetFovAsym; use NkCamera3D for engine-side
  // verification.
  Mat cameraQuest =
      asym(tan(rad(-52)), tan(rad(45)), tan(rad(48)), tan(rad(-50)), n, f);
  compare("test 2: angles asymetriques Quest (-52,45,48,-50) deg", manualQuest,
          cameraQuest);
}
