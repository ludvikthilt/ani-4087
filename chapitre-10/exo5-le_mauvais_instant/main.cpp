#include <cstdlib>
#include <iostream>

int main() {
    long long speed = 0;
    int imageCount = 0;
    if (!(std::cin >> speed >> imageCount)) {
        return 0;
    }

    long long falseImages = 0;
    long long worstHeadsetError = 0;
    long long worstSimulatorError = 0;

    for (int image = 1; image <= imageCount; ++image) {
        long long predictedTime = 0;
        long long submitTime = 0;
        long long displayTime = 0;
        char poseType = '\0';
        std::cin >> predictedTime >> submitTime >> displayTime >> poseType;

        const long long submittedTime =
            poseType == 'R' ? predictedTime : submitTime;
        const long long headsetError =
            speed * (submittedTime - predictedTime);
        const long long simulatorError =
            speed * (displayTime - predictedTime);

        std::cout << image << " CASQUE " << headsetError << " SIMULATEUR "
                  << simulatorError << '\n';
        if (headsetError != 0) {
            ++falseImages;
        }
        const long long absoluteHeadsetError = std::llabs(headsetError);
        const long long absoluteSimulatorError = std::llabs(simulatorError);
        if (absoluteHeadsetError > worstHeadsetError) {
            worstHeadsetError = absoluteHeadsetError;
        }
        if (absoluteSimulatorError > worstSimulatorError) {
            worstSimulatorError = absoluteSimulatorError;
        }
    }

    std::cout << "FAUSSES " << falseImages << '\n';
    std::cout << "PIRE CASQUE " << worstHeadsetError << '\n';
    std::cout << "PIRE SIMULATEUR " << worstSimulatorError << '\n';
}
