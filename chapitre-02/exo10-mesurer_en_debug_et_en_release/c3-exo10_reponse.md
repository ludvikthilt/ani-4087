## Énoncé

Nous écrivons une boucle de calcul chronométrée, la construisons en Debug puis en Release, mesurons son temps d'exécution, et déterminons laquelle des deux mesures nous aurait fait prendre une mauvaise décision, sachant qu'une image de casque dure 11 ms.

## Résolution

### Fichiers

**`main.cpp`**
```cpp
#include <iostream>
#include <chrono>
#include <vector>
#include <cstdint>

// Calcul lourd : test de primalité par essais de division
bool estPremier(uint64_t n) {
    if (n < 2) return false;
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
#ifdef NDEBUG
    std::cout << "--config Release\n";
#else
    std::cout << "--config Debug\n";
#endif

    const int nbEchantillons = 15;
    const uint64_t debutPlage = 10'000'000;
    const uint64_t tailleTest = 20'000;

    std::vector<double> mesures;
    mesures.reserve(nbEchantillons);

    uint64_t nombrePremiersTrouves = 0;

    for (int essai = 0; essai < nbEchantillons; essai++) {
        uint64_t base = debutPlage + static_cast<uint64_t>(essai) * tailleTest;

        auto debut = std::chrono::high_resolution_clock::now();

        for (uint64_t n = base; n < base + tailleTest; n++) {
            if (estPremier(n)) {
                nombrePremiersTrouves++;
            }
        }

        auto fin = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(fin - debut).count();
        mesures.push_back(ms);
    }

    double total = 0.0;
    for (double m : mesures) total += m;
    double moyenne = total / mesures.size();

    std::cout << "Echantillons testes    : " << nbEchantillons << "\n";
    std::cout << "Nombres par echantillon : " << tailleTest << "\n";
    std::cout << "Temps moyen             : " << moyenne << " ms\n";
    std::cout << "Nombres premiers trouves: " << nombrePremiersTrouves << "\n";

    return 0;
}
```

Le `#ifdef NDEBUG` sert uniquement à afficher la configuration active ; le calcul chronométré (test de primalité par essais de division) est identique dans les deux configurations.

### Exécution

### Sortie en Debug

#### Construction
```shell
Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Chrono [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Chrono                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Chrono\Chrono.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.42s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1.42s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
#### Exécution
```shell
--config Debug
Echantillons testes    : 15
Nombres par echantillon : 20000
Temps moyen             : 38.9847 ms
Nombres premiers trouves: 18599
```

### Sortie en Release
#### construction
```shell
Configuration: Release
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Chrono [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Chrono                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\release-Windows\Chrono\Chrono.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.91s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.91s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
#### Exécution
```shell
--config Release
Echantillons testes    : 15
Nombres par echantillon : 20000
Temps moyen             : 38.8304 ms
Nombres premiers trouves: 18599
```

### Tableau comparatif
| |Taille de l'éxécutable(o)|Temps de construction(ms)| Temps d'éxécution(ms)|
|---|---|---|---|
Debug| 109569|1423|38.9847|
Release| 109569|914| 38.8304|

>les mesures sont faite avec des commandes dédiées
>Les deux configurations ont des valeurs très proche mais Release prend légèrement moins de temps ici.

### Quelles mesures m'aurait fait prendre une mauvaise décision?
Dans ce cas précis les deux mesures sont largement au dessus des 11ms donc aucune ne convient réellement. Cependant celà peut etre du à la complicité du calcul ,et ainsi Release prend moins de temps de Debug donc dans l'idéal il correspondrait mieux, sachent egaleùent que les exécutables ont exactement la même taille.