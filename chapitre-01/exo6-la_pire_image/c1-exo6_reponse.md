## Enoncé

Sur un programme qui dessine en boucle (ou efface l'écran), mesurer sur 1000 images non pas la cadence moyenne mais la durée de la plus longue image, et le nombre d'images qui dépassent onze millisecondes.

## Protocole et mesure

Boucle de 1000 itérations effaçant un buffer d'image 1920×1080, chronométrée image par image.

## Code 

```cpp
#include <chrono>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>

int main() {
    const int width = 1920, height = 1080;
    std::vector<uint8_t> buffer(width * height * 4);

    const int frameCount = 1000;
    std::vector<double> times(frameCount);

    for (int i = 0; i < frameCount; ++i) {
        auto t0 = std::chrono::high_resolution_clock::now();
        std::memset(buffer.data(), 0, buffer.size()); // dessine - efface l'écran
        auto t1 = std::chrono::high_resolution_clock::now();
        times[i] = std::chrono::duration<double, std::milli>(t1 - t0).count();
    }

    double sum = 0, worst = 0;
    int over11 = 0, over83 = 0;
    for (double t : times) {
        sum += t;
        if (t > worst) worst = t;
        if (t > 11.0) over11++;
        if (t > 8.3) over83++;
    }

    std::printf("moyenne (ms): %.4f\n", sum / frameCount);
    std::printf("pire image (ms): %.4f\n", worst);
    std::printf("images > 11 ms: %d\n", over11);
    std::printf("images > 8.3 ms (120Hz): %d\n", over83);
    return 0;
}
```

## Résultat mesuré 

| Mesure | Valeur |
|---|---|
| Moyenne | 0,4228 ms |
| Pire image | 3,7854 ms |
| Images > 11 ms | 0 sur 1000 |
| Images > 8,3 ms (120 Hz) | 0 sur 1000 |

## Conclusion

Aucune image ne dépasse le budget ici. 
