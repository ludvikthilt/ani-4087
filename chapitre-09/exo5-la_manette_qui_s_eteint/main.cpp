#include <iostream>
#include <string>

int main() {
  int frameCount = 0;
  std::cin >> frameCount;

  std::string input;
  if (frameCount > 0)
    std::cin >> input;

  bool previousCurrent = false;
  bool heldWithActive = false;
  bool heldWithoutActive = false;
  bool fallenWithoutActive = false;
  int takesWithActive = 0;
  int takesWithoutActive = 0;
  int fallsWithoutActive = 0;
  int stuckFrames = 0;
  int differentFrames = 0;

  for (int i = 0; i < frameCount; ++i) {
    const char source = input[static_cast<std::size_t>(i)];
    const bool active = source != 'x';
    const bool current = source == '1';
    const bool changed = current != previousCurrent;
    previousCurrent = current;

    if (active && changed) {
      if (current) {
        heldWithActive = true;
        ++takesWithActive;
      } else {
        heldWithActive = false;
      }
    }

    if (changed) {
      if (current) {
        if (!fallenWithoutActive) {
          heldWithoutActive = true;
          ++takesWithoutActive;
        }
      } else if (heldWithoutActive) {
        heldWithoutActive = false;
        if (!active) {
          fallenWithoutActive = true;
          ++fallsWithoutActive;
        }
      }
    }

    if (source == '0' && heldWithActive)
      ++stuckFrames;
    if (heldWithActive != heldWithoutActive)
      ++differentFrames;

    std::cout << i + 1 << ' ' << (heldWithActive ? "TENU" : "LIBRE") << ' '
              << (heldWithoutActive ? "TENU" : "LIBRE") << '\n';
  }

  std::cout << "PRISES AVEC " << takesWithActive << '\n';
  std::cout << "PRISES SANS " << takesWithoutActive << '\n';
  std::cout << "CHUTES SANS " << fallsWithoutActive << '\n';
  std::cout << "COINCES AVEC " << stuckFrames << '\n';
  std::cout << "DIFFERENCES " << differentFrames << '\n';
  return 0;
}
