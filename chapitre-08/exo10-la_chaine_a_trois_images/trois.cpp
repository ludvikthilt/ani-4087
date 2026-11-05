#include <iostream>

int main() {
  int K;
  std::cin >> K;

  for (int s = 0; s < K; ++s) {
    long long n, L, T;
    std::cin >> n >> L >> T;

    long long conflits = 0;
    for (long long u = 1; u <= T; ++u) {
      const long long image = (u - 1) % n;

      bool conflit = false;
      for (long long d = 1; d <= L && u - d >= 1; ++d)
        if ((u - d - 1) % n == image)
          conflit = true;

      std::cout << u << ' ' << image << (conflit ? " CONFLIT" : "") << '\n';
      if (conflit)
        ++conflits;
    }
    std::cout << "CONFLITS " << n << ' ' << L << ' ' << conflits << '\n';
  }
  return 0;
}
