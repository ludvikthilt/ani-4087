#include <iostream>

int main() {
  long long hz = 0;
  long long ipd = 0;
  long long imageCount = 0;
  if (!(std::cin >> hz >> ipd >> imageCount)) {
    return 0;
  }
  long long x = 0;
  long long y = 0;
  long long z = 0;
  long long initialYaw = 0;
  long long yawStep = 0;
  long long xStep = 0;
  std::cin >> x >> y >> z >> initialYaw >> yawStep >> xStep;

  const long long period = hz <= 1 ? 72 : 1000000000LL / hz;
  std::cout << "PERIODE " << period << '\n';

  for (long long image = 1; image <= imageCount; ++image) {
    long long yaw = (initialYaw + (image - 1) * yawStep) % 4;
    if (yaw < 0) {
      yaw += 4;
    }
    long long rightX = 0;
    long long rightZ = 0;
    if (yaw == 0) {
      rightX = 1;
    } else if (yaw == 1) {
      rightZ = -1;
    } else if (yaw == 2) {
      rightX = -1;
    } else {
      rightZ = 1;
    }

    const long long currentX = x + (image - 1) * xStep;
    const long long halfIpd = ipd / 2;
    const long long leftX = currentX - rightX * halfIpd;
    const long long leftZ = z - rightZ * halfIpd;
    const long long rightEyeX = currentX + rightX * halfIpd;
    const long long rightEyeZ = z + rightZ * halfIpd;
    const long long instant = image * period;

    std::cout << image << " G " << leftX << ' ' << y << ' ' << leftZ << " D "
              << rightEyeX << ' ' << y << ' ' << rightEyeZ << " i " << instant
              << '\n';
  }
}
