#include <iostream>
#include <string>
#include <unordered_set>

int main() {
  long long speed = 0;
  int frameCount = 0;
  std::cin >> speed >> frameCount;

  long long offsetX = 0;
  long long offsetZ = 0;
  int diagonalFrames = 0;

  for (int frame = 1; frame <= frameCount; ++frame) {
    int yaw = 0;
    int commandCount = 0;
    std::cin >> yaw >> commandCount;
    std::unordered_set<std::string> held;
    for (int i = 0; i < commandCount; ++i) {
      std::string command;
      std::cin >> command;
      held.insert(command);
    }

    const int stickX = (held.count("F_DROITE") != 0) -
                       (held.count("F_GAUCHE") != 0);
    const int stickY = (held.count("F_HAUT") != 0) -
                       (held.count("F_BAS") != 0);
    if (stickX != 0 && stickY != 0)
      ++diagonalFrames;

    int forwardX = 0;
    int forwardZ = -1;
    int rightX = 1;
    int rightZ = 0;
    switch (yaw) {
    case 1:
      forwardX = -1;
      forwardZ = 0;
      rightX = 0;
      rightZ = -1;
      break;
    case 2:
      forwardX = 0;
      forwardZ = 1;
      rightX = -1;
      rightZ = 0;
      break;
    case 3:
      forwardX = 1;
      forwardZ = 0;
      rightX = 0;
      rightZ = 1;
      break;
    default:
      break;
    }

    offsetX += speed * (stickY * forwardX + stickX * rightX);
    offsetZ += speed * (stickY * forwardZ + stickX * rightZ);

    std::cout << frame << ' ' << stickX << ',' << stickY << ' ' << offsetX
              << ' ' << offsetZ << '\n';
  }

  std::cout << "DECALAGE " << offsetX << ' ' << offsetZ << '\n';
  std::cout << "DIAGONALES " << diagonalFrames << '\n';
  return 0;
}
