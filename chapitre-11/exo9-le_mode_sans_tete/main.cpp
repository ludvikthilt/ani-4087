#include <iostream>
#include <string>
#include <vector>

void printLarge(std::ostream &out, __int128 value) {
  if (value == 0) {
    out << '0';
    return;
  }
  if (value < 0) {
    out << '-';
    value = -value;
  }
  std::string digits;
  while (value > 0) {
    digits.push_back(static_cast<char>('0' + value % 10));
    value /= 10;
  }
  for (std::size_t i = digits.size(); i > 0; --i) {
    out << digits[i - 1];
  }
}

int main() {
  long long hz = 0;
  if (!(std::cin >> hz)) {
    return 0;
  }
  long long period = 72;
  if (hz > 1) {
    period = 1000000000LL / hz;
  }
  if (period <= 0) {
    period = 72;
  }

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
  if (count < 0) {
    count = 0;
  }
  std::vector<long long> clockA(static_cast<std::size_t>(count));
  std::vector<long long> clockB(static_cast<std::size_t>(count));
  for (long long &value : clockA) {
    std::cin >> value;
  }
  for (long long &value : clockB) {
    std::cin >> value;
  }

  std::cout << "PERIODE " << period << '\n';
  std::cout << "POSE " << yaw << ' ' << pitch << ' ' << x << ' ' << y << ' '
            << z << '\n';

  __int128 firstPredictedA = 0;
  __int128 firstPredictedB = 0;
  long long firstBrutDifference = 0;
  long long firstRelativeDifference = 0;
  for (int i = 0; i < count; ++i) {
    const __int128 predictedA = static_cast<__int128>(clockA[i]) + period;
    const __int128 predictedB = static_cast<__int128>(clockB[i]) + period;
    const __int128 brut = predictedB - predictedA;
    if (i == 0) {
      firstPredictedA = predictedA;
      firstPredictedB = predictedB;
    }
    const __int128 relativeA = predictedA - firstPredictedA;
    const __int128 relativeB = predictedB - firstPredictedB;
    const __int128 relative = relativeB - relativeA;
    if (brut != 0 && firstBrutDifference == 0) {
      firstBrutDifference = i + 1;
    }
    if (relative != 0 && firstRelativeDifference == 0) {
      firstRelativeDifference = i + 1;
    }
    std::cout << i + 1 << " BRUT ";
    printLarge(std::cout, brut);
    std::cout << " RELATIF ";
    printLarge(std::cout, relative);
    std::cout << " SCRIPTE " << (i + 1) * period << '\n';
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
