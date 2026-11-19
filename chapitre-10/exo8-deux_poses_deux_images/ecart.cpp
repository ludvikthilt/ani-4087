#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
    int imageCount = 0;
    long long frameTime = 0;
    if (!(std::cin >> imageCount >> frameTime)) {
        return 0;
    }

    long long positionSum = 0;
    long long angleSum = 0;

    for (int image = 1; image <= imageCount; ++image) {
        long long x1 = 0;
        long long z1 = 0;
        long long angle1 = 0;
        long long x2 = 0;
        long long z2 = 0;
        long long angle2 = 0;
        std::cin >> x1 >> z1 >> angle1 >> x2 >> z2 >> angle2;

        const long double dx = static_cast<long double>(x2 - x1);
        const long double dz = static_cast<long double>(z2 - z1);
        const long long position =
            std::llround(std::sqrt(dx * dx + dz * dz));
        const long long angle = std::llabs(angle2 - angle1);
        std::cout << image << " POSITION " << position << " ANGLE " << angle
                  << '\n';
        positionSum += position;
        angleSum += angle;
    }

    if (imageCount == 0 || frameTime == 0) {
        std::cout << "AUCUNE\n";
        return 0;
    }

    std::cout << "MOYENNE POSITION " << positionSum / imageCount << '\n';
    std::cout << "MOYENNE ANGLE " << angleSum / imageCount << '\n';
    std::cout << "VITESSE " << angleSum / (imageCount * frameTime) << '\n';
}
