#include <iostream>
#include <string>

int main() {
  int frameCount = 0;
  std::cin >> frameCount;

  std::string input;
  if (frameCount > 0)
    std::cin >> input;

  int previousCurrent = 0;
  int presses = 0;
  int releases = 0;
  int falseReleases = 0;
  int heldFrames = 0;

  for (int i = 0; i < frameCount; ++i) {
    const char source = input[static_cast<std::size_t>(i)];
    const int active = source == 'x' ? 0 : 1;
    const int current = source == '1' ? 1 : 0;
    const int changed = current != previousCurrent ? 1 : 0;

    if (current == 1 && changed == 1)
      ++presses;
    if (current == 0 && changed == 1) {
      ++releases;
      if (active == 0)
        ++falseReleases;
    }
    if (current == 1)
      ++heldFrames;

    std::cout << i + 1 << ' ' << current << ' ' << changed << ' ' << active
              << '\n';
    previousCurrent = current;
  }

  std::cout << "APPUIS " << presses << '\n';
  std::cout << "RELACHES " << releases << '\n';
  std::cout << "FAUX RELACHES " << falseReleases << '\n';
  std::cout << "TENUES " << heldFrames << '\n';
  return 0;
}
