#include <iostream>

int main() {
  int frameCount = 0;
  std::cin >> frameCount;

  int current = 0;
  int changed = 0;
  int active = 0;
  int previousPressed = 0;
  int realPresses = 0;
  int captures = 0;
  int refusedSyncs = 0;

  for (int frame = 1; frame <= frameCount; ++frame) {
    int pressed = 0;
    int syncCount = 0;
    int focused = 0;
    std::cin >> pressed >> syncCount >> focused;

    if (pressed == 1 && previousPressed == 0)
      ++realPresses;
    previousPressed = pressed;

    for (int sync = 0; sync < syncCount; ++sync) {
      if (focused == 0) {
        ++refusedSyncs;
        continue;
      }
      changed = pressed != current ? 1 : 0;
      current = pressed;
      active = 1;
    }

    const bool capturesNow = current == 1 && changed == 1;
    if (capturesNow)
      ++captures;
    std::cout << frame << ' ' << current << ' ' << changed << ' ' << active
              << ' ' << (capturesNow ? "SAISIT" : "-") << '\n';
  }

  std::cout << "APPUIS REELS " << realPresses << '\n';
  std::cout << "SAISIES " << captures << '\n';
  std::cout << "SYNC REFUSEES " << refusedSyncs << '\n';
  return 0;
}
