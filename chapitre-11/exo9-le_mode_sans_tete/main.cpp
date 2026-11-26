#include <iostream>
#include <string>
#include <vector>

int main() {
    long long hz = 0;
    if (!(std::cin >> hz)) {
        return 0;
    }
    const long long period = hz <= 1 ? 72 : 1000000000LL / hz;

    std::string poseMode;
    std::cin >> poseMode;
    long long yaw = 0;
    long long pitch = 0;
    long long x = 0;
    long long y = 1700;
    long long z = 0;
    if (poseMode == "FIXE") {
        std::cin >> yaw >> pitch >> x >> y >> z;
    }

    int count = 0;
    std::cin >> count;
    std::vector<long long> clockA(static_cast<std::size_t>(count));
    std::vector<long long> clockB(static_cast<std::size_t>(count));
    for (long long &value : clockA) {
        std::cin >> value;
    }
    for (long long &value : clockB) {
        std::cin >> value;
    }

    std::cout << "PERIODE " << period << '\n';
    std::cout << "POSE " << yaw << ' ' << pitch << ' ' << x << ' ' << y
              << ' ' << z << '\n';

    long long firstPredictedA = 0;
    long long firstPredictedB = 0;
    long long firstBrutDifference = 0;
    long long firstRelativeDifference = 0;
    for (int i = 0; i < count; ++i) {
        const long long predictedA = clockA[i] + period;
        const long long predictedB = clockB[i] + period;
        const long long brut = predictedB - predictedA;
        if (i == 0) {
            firstPredictedA = predictedA;
            firstPredictedB = predictedB;
        }
        const long long relativeA =
            predictedA - firstPredictedA;
        const long long relativeB =
            predictedB - firstPredictedB;
        const long long relative = relativeB - relativeA;
        if (brut != 0 && firstBrutDifference == 0) {
            firstBrutDifference = i + 1;
        }
        if (relative != 0 && firstRelativeDifference == 0) {
            firstRelativeDifference = i + 1;
        }
        std::cout << i + 1 << " BRUT " << brut << " RELATIF "
                  << relative << " SCRIPTE " << (i + 1) * period << '\n';
    }

    if (firstBrutDifference == 0) {
        std::cout << "BRUT IDENTIQUE\n";
    } else {
        std::cout << "BRUT DIFFERENT " << firstBrutDifference << '\n';
    }
    if (firstRelativeDifference == 0) {
        std::cout << "RELATIF IDENTIQUE\n";
    } else {
        std::cout << "RELATIF DIFFERENT " << firstRelativeDifference << '\n';
    }
}
