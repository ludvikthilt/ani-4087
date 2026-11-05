#include <cstdint>
#include <iostream>

int main() {
  std::uint64_t N;
  std::cin >> N;

  std::uint64_t refusees = 0, fauxSigne = 0, fauxNonSigne = 0;

  for (std::uint64_t i = 0; i < N; ++i) {
    std::uint64_t n, r;
    std::cin >> n >> r;
    if (n == 0 || n > 4) {
      std::cout << n << ' ' << r << " REFUSEE\n";
      ++refusees;
      continue;
    }

    const std::uint64_t prochaine = r % n;
    const std::uint64_t juste = (prochaine + n - 1) % n;

    const int signe = (static_cast<int>(prochaine) - 1) % static_cast<int>(n);
    const std::uint32_t nonSigne =
        (static_cast<std::uint32_t>(prochaine) - 1u) %
        static_cast<std::uint32_t>(n);

    std::cout << n << ' ' << r << ' ' << prochaine << ' ' << juste << ' '
              << signe << ' ' << nonSigne << '\n';

    if (signe != static_cast<int>(juste))
      ++fauxSigne;
    if (nonSigne != juste)
      ++fauxNonSigne;
  }

  std::cout << "REFUSEES " << refusees << '\n';
  std::cout << "FAUX SIGNE " << fauxSigne << '\n';
  std::cout << "FAUX NON SIGNE " << fauxNonSigne << '\n';
  return 0;
}
