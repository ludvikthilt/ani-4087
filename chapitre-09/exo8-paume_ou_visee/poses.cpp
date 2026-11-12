#include <cmath>
#include <iostream>
#include <vector>

struct Vector3 {
  long long x;
  long long y;
  long long z;
};

constexpr Vector3 kPalmRight{180, -300, -250};
constexpr Vector3 kAimRight{180, -250, -400};

Vector3 rotateForYaw(Vector3 point, int yaw) {
  switch (yaw) {
  case 1:
    return {point.z, point.y, -point.x};
  case 2:
    return {-point.x, point.y, -point.z};
  case 3:
    return {-point.z, point.y, point.x};
  default:
    return point;
  }
}

Vector3 worldPosition(const Vector3& head, Vector3 local, int yaw) {
  const Vector3 rotated = rotateForYaw(local, yaw);
  return {head.x + rotated.x, head.y + rotated.y, head.z + rotated.z};
}

int nearestReachable(const Vector3& hand, const std::vector<Vector3>& objects) {
  long long nearestDistance = 150LL * 150LL;
  int nearest = -1;
  for (std::size_t i = 0; i < objects.size(); ++i) {
    const long long dx = objects[i].x - hand.x;
    const long long dy = objects[i].y - hand.y;
    const long long dz = objects[i].z - hand.z;
    const long long distance = dx * dx + dy * dy + dz * dz;
    if (distance <= nearestDistance) {
      if (nearest == -1 || distance < nearestDistance) {
        nearestDistance = distance;
        nearest = static_cast<int>(i);
      }
    }
  }
  return nearest;
}

int main() {
  int headCount = 0;
  int objectCount = 0;
  std::cin >> headCount >> objectCount;

  std::vector<Vector3> heads(static_cast<std::size_t>(headCount));
  std::vector<int> yaws(static_cast<std::size_t>(headCount));
  for (int i = 0; i < headCount; ++i) {
    std::cin >> heads[static_cast<std::size_t>(i)].x >>
        heads[static_cast<std::size_t>(i)].y >>
        heads[static_cast<std::size_t>(i)].z >>
        yaws[static_cast<std::size_t>(i)];
  }

  std::vector<Vector3> objects(static_cast<std::size_t>(objectCount));
  for (Vector3& object : objects)
    std::cin >> object.x >> object.y >> object.z;

  for (int i = 0; i < headCount; ++i) {
    const Vector3& head = heads[static_cast<std::size_t>(i)];
    const int yaw = yaws[static_cast<std::size_t>(i)];
    const Vector3 palmRight = worldPosition(head, kPalmRight, yaw);
    const Vector3 aimRight = worldPosition(head, kAimRight, yaw);
    const Vector3 palmLeft =
        worldPosition(head, {-180, -300, -250}, yaw);
    const Vector3 aimLeft =
        worldPosition(head, {-180, -250, -400}, yaw);

    std::cout << "TETE " << i + 1 << '\n';
    std::cout << "PAUME D " << palmRight.x << ' ' << palmRight.y << ' '
              << palmRight.z << '\n';
    std::cout << "VISEE D " << aimRight.x << ' ' << aimRight.y << ' '
              << aimRight.z << '\n';
    std::cout << "PAUME G " << palmLeft.x << ' ' << palmLeft.y << ' '
              << palmLeft.z << '\n';
    std::cout << "VISEE G " << aimLeft.x << ' ' << aimLeft.y << ' '
              << aimLeft.z << '\n';

    const int palmTarget = nearestReachable(palmRight, objects);
    if (palmTarget == -1)
      std::cout << "SAISIE PAUME AUCUNE\n";
    else
      std::cout << "SAISIE PAUME " << palmTarget + 1 << '\n';

    const int aimTarget = nearestReachable(aimRight, objects);
    if (aimTarget == -1)
      std::cout << "SAISIE VISEE AUCUNE\n";
    else
      std::cout << "SAISIE VISEE " << aimTarget + 1 << '\n';

  }

  const long long dx = kPalmRight.x - kAimRight.x;
  const long long dy = kPalmRight.y - kAimRight.y;
  const long long dz = kPalmRight.z - kAimRight.z;
  const double distance =
      std::sqrt(static_cast<double>(dx * dx + dy * dy + dz * dz));
  std::cout << "ECART " << std::llround(distance) << '\n';
  return 0;
}
