# Exercice - La Borne des Cent Millisecondes

## Énoncé
Extrapolez une pose de tête qui tourne à une vitesse réaliste, disons cent quatre-vingts degrés par seconde, sur des durées croissantes de dix millisecondes à une seconde.

Comparez chaque résultat à la vraie pose, obtenue en simulant le mouvement pas à pas. Rendez la courbe de l'erreur et dites où la borne de cent millisecondes se justifie.

## Démonstration

### On a
Une pose de tête au repos, position (0, 0, 0), quaternion (0, 0, 0, 1).

Une vitesse angulaire instantanée initiale ω0 = 180 °/s, prise comme constante par le modèle d'extrapolation.

Un mouvement réel de tête qui ne maintient pas cette vitesse indéfiniment, une rotation humaine réelle décélère après son amorce, la vitesse angulaire instantanée du mouvement réel décroît exponentiellement avec une constante de temps τ :

ω(t) = ω0 · e^(-t/τ), τ = 0.3 s

### Ainsi
Le modèle extrapolé intègre la vitesse constante ω0 :

θ_extrapolé(t) = ω0 · t

Le mouvement réel s'obtient par intégration pas à pas, en accumulant ω(s) sur de petits sous-intervalles de 0 à t, ce qui donne analytiquement :

θ_vrai(t) = ∫₀ᵗ ω0·e^(-s/τ) ds = ω0·τ·(1 - e^(-t/τ))

L'erreur entre les deux modèles est alors :

erreur(t) = θ_extrapolé(t) - θ_vrai(t) = ω0·t - ω0·τ·(1 - e^(-t/τ))

Pour t petit devant τ, e^(-t/τ) ≈ 1 - t/τ + t²/(2τ²), donc θ_vrai(t) ≈ ω0·t - ω0·t²/(2τ), et l'erreur croît d'abord quadratiquement, erreur(t) ≈ ω0·t²/(2τ). Ainsi pour t = 100 ms, erreur ≈ 180 × 0.01/(2 × 0.3) = 3.0°, cohérent avec l'ordre de grandeur observé. Pour t comparable ou supérieur à τ, l'approximation quadratique n'est plus valable et l'écart croît plus rapidement, car θ_vrai(t) plafonne vers ω0·τ = 54° pendant que θ_extrapolé(t) continue de croître linéairement sans borne.

### Conclusion

    dt (ms)   extrapole (deg)   vrai (deg)   erreur (deg)
    10.0000            1.8000       1.7703         0.0297
    20.0000            3.6000       3.4826         0.1174
    50.0000            9.0000       8.2900         0.7100
    100.0000           18.0000      15.3073         2.6927
    200.0000           36.0000      26.2755         9.7245
    300.0000           54.0000      34.1345        19.8655
    500.0000           90.0000      43.8007        46.1993
    750.0000          135.0000      49.5674        85.4326
    1000.0000          180.0000      52.0736       127.9264

### Observation
En dessous de cent millisecondes, l'erreur reste inférieure à trois degrés, une valeur suffisamment faible pour rester imperceptible dans la plupart des contextes de rendu. Au delà, l'écart entre le modèle linéaire et le mouvement réel croît d'abord de façon quadratique puis s'aggrave nettement à mesure que la vraie rotation plafonne pendant que l'extrapolation continue indéfiniment, atteignant 127.93° d'erreur à une seconde. C'est cette rupture de comportement, quadratique puis rapidement divergente, qui justifie de borner l'extrapolation à cent millisecondes.

## Code

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

double angleExtrapole(double omega0Deg, double t) {
    return omega0Deg * t;
}

double angleVraiSimule(double omega0Deg, double tau, double t, double pas) {
    double angle = 0.0;
    double temps = 0.0;
    while (temps < t) {
        double h = std::min(pas, t - temps);
        double omega = omega0Deg * std::exp(-temps / tau);
        angle += omega * h;
        temps += h;
    }
    return angle;
}

int main() {
    double omega0 = 180.0;
    double tau = 0.3;
    double pasSimulation = 1e-4;

    std::vector<double> dts = { 0.010, 0.020, 0.050, 0.100, 0.200, 0.300, 0.500, 0.750, 1.000 };

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "dt (ms)   extrapole (deg)   vrai (deg)   erreur (deg)\n";

    for (double dt : dts) {
        double extrapole = angleExtrapole(omega0, dt);
        double vrai = angleVraiSimule(omega0, tau, dt, pasSimulation);
        double erreur = extrapole - vrai;

        std::cout << dt * 1000.0 << "\t" << extrapole << "\t" << vrai << "\t" << erreur << "\n";
    }

    return 0;
}
```
