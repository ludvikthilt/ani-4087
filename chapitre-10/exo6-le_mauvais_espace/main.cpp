#include <iostream>

struct Pose {
    long long x;
    long long y;
    long long z;
    int yaw;
};

Pose compose(const Pose &anchor, const Pose &pose) {
    long long rotatedX = pose.x;
    long long rotatedZ = pose.z;
    switch (anchor.yaw) {
    case 1:
        rotatedX = pose.z;
        rotatedZ = -pose.x;
        break;
    case 2:
        rotatedX = -pose.x;
        rotatedZ = -pose.z;
        break;
    case 3:
        rotatedX = -pose.z;
        rotatedZ = pose.x;
        break;
    default:
        break;
    }

    return {anchor.x + rotatedX, anchor.y + pose.y, anchor.z + rotatedZ,
            (anchor.yaw + pose.yaw) % 4};
}

int main() {
    Pose anchor{};
    Pose eye{};
    int poseCount = 0;
    if (!(std::cin >> anchor.x >> anchor.y >> anchor.z >> anchor.yaw >>
          eye.x >> eye.y >> eye.z >> poseCount)) {
        return 0;
    }

    int correct = 0;
    int faulty = 0;
    for (int index = 1; index <= poseCount; ++index) {
        char requestedSpace = '\0';
        char layerSpace = '\0';
        Pose pose{};
        std::cin >> requestedSpace >> layerSpace >> pose.x >> pose.y >>
            pose.z >> pose.yaw;

        const Pose actual = requestedSpace == 'L' ? compose(anchor, pose) : pose;
        const Pose believed = layerSpace == 'L' ? compose(anchor, pose) : pose;
        const long long deltaX = believed.x - actual.x;
        const long long deltaY = believed.y - actual.y;
        const long long deltaZ = believed.z - actual.z;
        const int deltaYaw = (believed.yaw - actual.yaw + 4) % 4;

        std::cout << index << " CRU " << believed.x << ' ' << believed.y << ' '
                  << believed.z << ' ' << believed.yaw << '\n';
        std::cout << index << " ECART " << deltaX << ' ' << deltaY << ' '
                  << deltaZ << ' ' << deltaYaw << '\n';

        if (deltaX == 0 && deltaY == 0 && deltaZ == 0 && deltaYaw == 0) {
            ++correct;
        } else {
            ++faulty;
        }
    }

    std::cout << "JUSTES " << correct << '\n';
    std::cout << "FAUSSES " << faulty << '\n';
}
