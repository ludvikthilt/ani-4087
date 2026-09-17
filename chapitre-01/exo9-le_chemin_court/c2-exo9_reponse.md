# Exercice - Le Chemin Court

## Énoncé
Écrivez la vitesse angulaire moyenne entre deux orientations séparées de dt, avec le forçage du chemin court.

Puis retirez le forçage et trouvez deux quaternions pour lesquels le résultat devient absurde. Rendez les deux valeurs, avec et sans.

## Démonstration

### On a
Deux quaternions unitaires q1 et q2 représentant l'orientation à deux instants séparés de dt.

q1 = (0, 0, 0, 1), q2 = (0, 0, -0.0049999, -0.9999875), dt = 0.01 s

Un même quaternion et son opposé, q et -q, représentent la même orientation. Le quotient q2 ⊗ q1⁻¹ n'est donc pas unique, il existe deux représentants possibles de la rotation relative, l'un correspondant au chemin court, l'autre à un tour presque complet dans l'autre sens.

### Ainsi
Le forçage du chemin court consiste à imposer un produit scalaire positif entre les deux quaternions avant de calculer leur écart, en inversant le signe de q2 si q1 · q2 < 0.

q1 · q2 = w1·w2 + x1·x2 + y1·y2 + z1·z2

Ici q1 · q2 = 1 × (-0.9999875) = -0.9999875 < 0, le chemin sans forçage traverse donc la longue route.

Soit dq = q2 ⊗ q1⁻¹ le quaternion de rotation relative, dq = (v, s) avec v sa partie vectorielle et s sa partie scalaire. L'angle de rotation associé est :

θ = 2·atan2(‖v‖, s)

et l'axe n = v/‖v‖. La vitesse angulaire moyenne s'obtient par :

w = (θ/dt)·n

Sans forçage, dq = q2 (car q1 est l'identité), v = (0, 0, -0.0049999), ‖v‖ = 0.0049999, s = -0.9999875. Comme s est négatif, θ = 2·atan2(0.0049999, -0.9999875) est proche de 2π, ici θ ≈ 6.2732 rad. La vitesse angulaire obtenue vaut alors w = (θ/0.01)·n ≈ (0, 0, -627.3079) rad/s, une norme aberrante pour un mouvement aussi petit.

Avec forçage, q1 · q2 < 0 impose de remplacer q2 par -q2 = (0, 0, 0.0049999, 0.9999875). Le même calcul donne alors s = 0.9999875 positif, θ = 2·atan2(0.0049999, 0.9999875) ≈ 0.01 rad, et w = (θ/0.01)·n ≈ (0, 0, 1.0000) rad/s, valeur cohérente avec un petit mouvement de rotation sur dt = 0.01 s.

### Conclusion

    Sans forcage : 0.0000  0.0000  -627.3079   (norme : 627.3079 rad/s)
    Avec forcage : 0.0000  -0.0000  1.0000   (norme : 1.0000 rad/s)

### Observation
Sans forçage, la norme explose, comme si la rotation avait effectué des tours complets supplémentaires sur un petit mouvement. Le signe du produit scalaire entre les deux quaternions révèle que le chemin court et le chemin non forcé ne coïncident pas, d'où l'importance de la recherche systématique du chemin le plus court avant tout calcul de vitesse angulaire.

## Code

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

struct Quat {
    double x, y, z, w;
};

struct Vec3 {
    double x, y, z;
};

double dot(const Quat& a, const Quat& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quat conj(const Quat& q) {
    return { -q.x, -q.y, -q.z, q.w };
}

Quat negate(const Quat& q) {
    return { -q.x, -q.y, -q.z, -q.w };
}

Quat quatMul(const Quat& a, const Quat& b) {
    return {
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    };
}

Vec3 averageAngularVelocity(const Quat& q1, const Quat& q2, double dt, bool forceShortPath) {
    Quat b = q2;
    if (forceShortPath && dot(q1, q2) < 0.0) {
        b = negate(q2);
    }
    Quat dq = quatMul(b, conj(q1));

    Vec3 v = { dq.x, dq.y, dq.z };
    double normV = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (normV < 1e-12) {
        return { 0.0, 0.0, 0.0 };
    }

    double theta = 2.0 * std::atan2(normV, dq.w);
    Vec3 axis = { v.x / normV, v.y / normV, v.z / normV };

    return { axis.x * theta / dt, axis.y * theta / dt, axis.z * theta / dt };
}

int main() {
    Quat q1, q2;
    double dt;

    std::cout << "Entrez q1 (x y z w)\n";
    std::cin >> q1.x >> q1.y >> q1.z >> q1.w;

    std::cout << "Entrez q2 (x y z w)\n";
    std::cin >> q2.x >> q2.y >> q2.z >> q2.w;

    std::cout << "Entrez dt, en secondes\n";
    std::cin >> dt;

    Vec3 sans = averageAngularVelocity(q1, q2, dt, false);
    Vec3 avec = averageAngularVelocity(q1, q2, dt, true);

    double normeSans = std::sqrt(sans.x * sans.x + sans.y * sans.y + sans.z * sans.z);
    double normeAvec = std::sqrt(avec.x * avec.x + avec.y * avec.y + avec.z * avec.z);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Sans forcage : " << sans.x << "  " << sans.y << "  " << sans.z
              << "   (norme : " << normeSans << " rad/s)\n";
    std::cout << "Avec forcage : " << avec.x << "  " << avec.y << "  " << avec.z
              << "   (norme : " << normeAvec << " rad/s)\n";

    return 0;
}
```
