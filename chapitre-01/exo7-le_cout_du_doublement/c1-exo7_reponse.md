## Enoncé

Mesurer le temps de rendu seul (sans la logique). Estimer ce que coûterait ce rendu fait deux fois, et ce qu'il resterait pour le reste.

## Code 

```cpp
#include <chrono>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

int main() {
    const int width = 1920, height = 1080;
    std::vector<uint8_t> buffer(width * height * 4);

    const int frameCount = 1000;
    std::vector<double> logicTimes(frameCount);
    std::vector<double> renderTimes(frameCount);

    float x = 0.0f, v = 1.0f;

    for (int i = 0; i < frameCount; ++i) {
        // --- logique simpliste  ---
        auto l0 = std::chrono::high_resolution_clock::now();
        for (int s = 0; s < 1000; ++s) {
            v += std::sin(x) * 0.001f;
            x += v * 0.001f;
        }
        auto l1 = std::chrono::high_resolution_clock::now();
        logicTimes[i] = std::chrono::duration<double, std::milli>(l1 - l0).count();

        // --- rendu  ---
        auto r0 = std::chrono::high_resolution_clock::now();
        std::memset(buffer.data(), 0, buffer.size());
        auto r1 = std::chrono::high_resolution_clock::now();
        renderTimes[i] = std::chrono::duration<double, std::milli>(r1 - r0).count();
    }

    double logicSum = 0, renderSum = 0;
    for (int i = 0; i < frameCount; ++i) {
        logicSum += logicTimes[i];
        renderSum += renderTimes[i];
    }
    double logicAvg = logicSum / frameCount;
    double renderAvg = renderSum / frameCount;
    double renderDoubled = renderAvg * 2.0;

    const double budget90Hz = 3.1; 
    double remaining = budget90Hz - renderDoubled;

    std::printf("logique seule (ms): %.4f\n", logicAvg);
    std::printf("rendu, un oeil (ms): %.4f\n", renderAvg);
    std::printf("rendu doublé, deux yeux (ms): %.4f\n", renderDoubled);
    std::printf("budget code a 90Hz (ms): %.4f\n", budget90Hz);
    std::printf("reste apres rendu double (ms): %.4f\n", remaining);
    return 0;
}
```

## Résultat mesuré 

| Mesure | Valeur |
|---|---|
| Logique seule | 0,0292 ms |
| Rendu, un œil | 0,8118 ms |
| Rendu doublé, deux yeux | 1,6236 ms |
| Budget code à 90 Hz | 3,1 ms |
| **Reste après rendu doublé** | **1,4764 ms** |

## Conclusion

Sur ce programme minimal, doubler le rendu ne coûte presque rien. 
