#include <iostream>
#include <string>

int main() {
    int swapchainSize = 0;
    int imageCount = 0;
    if (!(std::cin >> swapchainSize >> imageCount)) {
        return 0;
    }

    std::string renderFlags;
    if (imageCount > 0) {
        std::cin >> renderFlags;
    }

    if (swapchainSize < 1 || swapchainSize > 4) {
        std::cout << "CHAINE REFUSEE\n";
        return 0;
    }

    int nextImage = 0;
    int rendered = 0;
    int skipped = 0;

    for (int frame = 1; frame <= imageCount; ++frame) {
        if (renderFlags[static_cast<std::size_t>(frame - 1)] == '1') {
            std::cout << frame << " OUI " << frame - 1 << ' ' << nextImage
                      << '\n';
            nextImage = (nextImage + 1) % swapchainSize;
            ++rendered;
        } else {
            std::cout << frame << " NON 0\n";
            ++skipped;
        }
    }

    std::cout << "FINS " << imageCount << '\n';
    std::cout << "RENDUES " << rendered << '\n';
    std::cout << "SAUTEES " << skipped << '\n';
    std::cout << "PROCHAINE " << nextImage << '\n';
}
