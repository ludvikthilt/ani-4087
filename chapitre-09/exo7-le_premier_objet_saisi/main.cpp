#include <iostream>
#include <limits>
#include <vector>

struct Point {
  long long x;
  long long y;
};

struct Pose {
  long long x;
  long long y;
  int angle;
};

Point rotate(Point point, int angle) {
  switch (angle) {
  case 1:
    return {-point.y, point.x};
  case 2:
    return {-point.x, -point.y};
  case 3:
    return {point.y, -point.x};
  default:
    return point;
  }
}

Pose compose(const Pose& first, const Pose& second) {
  const Point rotated = rotate({second.x, second.y}, first.angle);
  return {first.x + rotated.x, first.y + rotated.y,
          (first.angle + second.angle) % 4};
}

Pose inverse(const Pose& pose) {
  const int inverseAngle = (4 - pose.angle) % 4;
  const Point inversePosition = rotate({-pose.x, -pose.y}, inverseAngle);
  return {inversePosition.x, inversePosition.y, inverseAngle};
}

int main() {
  int objectCount = 0;
  int frameCount = 0;
  std::cin >> objectCount >> frameCount;

  std::vector<Pose> objects(static_cast<std::size_t>(objectCount));
  for (Pose& object : objects)
    std::cin >> object.x >> object.y >> object.angle;

  int heldObject = -1;
  Pose attachment{0, 0, 0};
  int previousPressed = 0;
  int successfulTakes = 0;
  int missedTakes = 0;

  for (int frame = 1; frame <= frameCount; ++frame) {
    Pose palm;
    int pressed = 0;
    std::cin >> palm.x >> palm.y >> palm.angle >> pressed;

    const bool risingEdge = pressed == 1 && previousPressed == 0;
    const bool fallingEdge = pressed == 0 && previousPressed == 1;
    previousPressed = pressed;

    bool missedThisFrame = false;
    if (risingEdge && heldObject == -1) {
      long long nearestDistance = std::numeric_limits<long long>::max();
      int nearestObject = -1;
      for (std::size_t i = 0; i < objects.size(); ++i) {
        const long long dx = objects[i].x - palm.x;
        const long long dy = objects[i].y - palm.y;
        const long long distance = dx * dx + dy * dy;
        if (distance <= 22500 && distance < nearestDistance) {
          nearestDistance = distance;
          nearestObject = static_cast<int>(i);
        }
      }

      if (nearestObject == -1) {
        ++missedTakes;
        missedThisFrame = true;
      } else {
        heldObject = nearestObject;
        attachment = compose(inverse(palm), objects[static_cast<std::size_t>(heldObject)]);
        ++successfulTakes;
      }
    } else if (fallingEdge) {
      heldObject = -1;
    }

    if (heldObject != -1) {
      Pose& object = objects[static_cast<std::size_t>(heldObject)];
      object = compose(palm, attachment);
      std::cout << frame << " TIENT " << heldObject + 1 << ' ' << object.x
                << ' ' << object.y << ' ' << object.angle << '\n';
    } else if (missedThisFrame) {
      std::cout << frame << " RATE\n";
    } else {
      std::cout << frame << " LIBRE\n";
    }
  }

  std::cout << "SAISIES " << successfulTakes << '\n';
  std::cout << "RATEES " << missedTakes << '\n';
  for (std::size_t i = 0; i < objects.size(); ++i) {
    std::cout << "OBJET " << i + 1 << ' ' << objects[i].x << ' '
              << objects[i].y << ' ' << objects[i].angle << '\n';
  }
  return 0;
}
