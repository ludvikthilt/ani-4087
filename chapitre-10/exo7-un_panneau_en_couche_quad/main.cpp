#include <cmath>
#include <iostream>

struct Point {
    long long x;
    long long y;
    long long z;
};

Point rotate(const Point &point, int yaw) {
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

int main() {
    Point anchor{};
    int anchorYaw = 0;
    Point eye{};
    int panelCount = 0;
    if (!(std::cin >> anchor.x >> anchor.y >> anchor.z >> anchorYaw >>
          eye.x >> eye.y >> eye.z >> panelCount)) {
        return 0;
    }

    for (int index = 1; index <= panelCount; ++index) {
        char space = '\0';
        Point center{};
        int yaw = 0;
        long long width = 0;
        long long height = 0;
        std::cin >> space >> center.x >> center.y >> center.z >> yaw >> width >>
            height;

        const bool isLocal = space != 'S';
        const int stageYaw = isLocal ? (anchorYaw + yaw) % 4 : yaw;
        if (isLocal) {
            const Point offset = rotate(center, anchorYaw);
            center = {anchor.x + offset.x, anchor.y + offset.y,
                      anchor.z + offset.z};
        }

        std::cout << "PANNEAU " << index << " ESPACE "
                  << (isLocal ? "LOCAL" : "STAGE") << '\n';

        const Point corners[] = {
            {-width / 2, -height / 2, 0},
            {width / 2, -height / 2, 0},
            {width / 2, height / 2, 0},
            {-width / 2, height / 2, 0},
        };
        for (const Point &corner : corners) {
            const Point offset = rotate(corner, stageYaw);
            std::cout << center.x + offset.x << ' ' << center.y + offset.y
                      << ' ' << center.z + offset.z << '\n';
        }

        const long double dx = static_cast<long double>(center.x - eye.x);
        const long double dy = static_cast<long double>(center.y - eye.y);
        const long double dz = static_cast<long double>(center.z - eye.z);
        const long long distance = std::llround(std::sqrt(dx * dx + dy * dy + dz * dz));
        std::cout << "DISTANCE " << distance << '\n';
    }

    std::cout << "PANNEAUX " << panelCount << '\n';
}
