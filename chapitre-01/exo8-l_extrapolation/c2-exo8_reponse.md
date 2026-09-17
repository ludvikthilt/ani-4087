# Exercice - L'extrapolation

## Énoncé
Écrivez la fonction qui avance une pose de dt secondes à vitesses constantes, linéaire et angulaire.

Votre programme lit une pose, ses deux vitesses et une durée, et affiche la pose extrapolée. Traitez le cas d'une vitesse angulaire nulle sans diviser par zéro.

## Démonstration

### On a
Une pose initiale composée d'une position p0 et d'un quaternion unitaire q0.

p0 = (-1, 0, 2), q0 = (0.1221, 0.4517, -0.4945, -0.7325)

Une vitesse linéaire v = (1, 1, 2) m/s et une vitesse angulaire w = (0, 0.2, 0.56) rad/s, ainsi qu'une durée dt.

La position suit un modèle purement linéaire, l'orientation suit un modèle de rotation à vitesse angulaire constante autour d'un axe fixe pendant dt.

### Ainsi
La position à l'instant dt s'obtient par intégration triviale de la vitesse constante :

p(dt) = p0 + v·dt

Pour l'orientation, soit ω = ‖w‖ la norme de la vitesse angulaire.

Si ω = 0, aucun axe de rotation n'est défini, on pose le quaternion delta dq à l'identité, dq = (0, 0, 0, 1), et donc q(dt) = q0. Il n'y a ainsi jamais de division par zéro.

Si ω ≠ 0, soit n = w/ω l'axe unitaire de rotation, et θ = ω·dt l'angle balayé pendant dt. Le quaternion delta s'écrit :

dq = (nx·sin(θ/2), ny·sin(θ/2), nz·sin(θ/2), cos(θ/2))

La pose extrapolée s'obtient alors par :

p(dt) = p0 + v·dt
q(dt) = normaliser(dq ⊗ q0)

la normalisation compensant les erreurs d'arrondi accumulées dans le produit de quaternions.

Pour dt = 2 s, ω = √(0.2² + 0.56²) = √0.3536 ≈ 0.5946 rad/s, θ ≈ 1.1893 rad. Le calcul de p(2) et de dq ⊗ q0 normalisé donne le premier résultat ci-dessous.

Pour ω = 0, dq est l'identité quel que soit dt, donc q(dt) = q0.

Pour dt = 20 s, θ ≈ 11.893 rad, la même formule s'applique et donne le troisième résultat.

### Conclusion
Pour dt = 2 s, avec vitesse angulaire :

    Pose extrapolee :
    Position   : 1.0000  2.0000  6.0000
    Quaternion : -0.2303  0.3006  -0.8191  -0.4310

Pour dt = 2 s, avec vitesse angulaire nulle :

    Pose extrapolee :
    Position   : 1.0000  2.0000  6.0000
    Quaternion : 0.1221  0.4517  -0.4945  -0.7325

Pour dt = 20 s, avec vitesse angulaire :

    Pose extrapolee :
    Position   : 19.0000  20.0000  42.0000
    Quaternion : 0.3108  0.4697  -0.2252  -0.7950

### Observation
Il y a conservation de l'orientation en cas de vitesse angulaire nulle, seule la position évolue.

Sur vingt secondes, le mouvement extrapolé suppose qu'un corps conserve la même vitesse linéaire et angulaire pendant tout cet intervalle, ce qui est fort improbable pour un mouvement réel. Le modèle à vitesse constante ment donc plus qu'il n'aide au delà d'un court intervalle.

## Code

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

struct Vec3 {
    double x, y, z;
};

struct Quat {
    double x, y, z, w;
};

double norm(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 extrapolatePosition(const Vec3& p, const Vec3& v, double dt) {
    return { p.x + v.x * dt, p.y + v.y * dt, p.z + v.z * dt };
}

Quat quatMul(const Quat& a, const Quat& b) {
    return {
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    };
}

Quat quatNormalize(const Quat& q) {
    double n = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return { q.x / n, q.y / n, q.z / n, q.w / n };
}

Quat deltaQuat(const Vec3& w, double dt) {
    double omega = norm(w);
    if (omega < 1e-12) {
        return { 0.0, 0.0, 0.0, 1.0 };
    }
    Vec3 axis = { w.x / omega, w.y / omega, w.z / omega };
    double theta = omega * dt;
    double s = std::sin(theta / 2.0);
    double c = std::cos(theta / 2.0);
    return { axis.x * s, axis.y * s, axis.z * s, c };
}

Quat extrapolateOrientation(const Quat& q, const Vec3& w, double dt) {
    Quat dq = deltaQuat(w, dt);
    return quatNormalize(quatMul(dq, q));
}

int main() {
    Vec3 p, v, w;
    Quat q;
    double dt;

    std::cout << "Entrez la position de la pose\n";
    std::cin >> p.x >> p.y >> p.z;

    std::cout << "Entrez le quaternion unitaire de la pose\n";
    std::cin >> q.x >> q.y >> q.z >> q.w;

    std::cout << "Entrez la vitesse lineaire, m/s (x y z)\n";
    std::cin >> v.x >> v.y >> v.z;

    std::cout << "Entrez la vitesse angulaire, rad/s (x y z)\n";
    std::cin >> w.x >> w.y >> w.z;

    std::cout << "Entrez dt, en secondes\n";
    std::cin >> dt;

    Vec3 pNew = extrapolatePosition(p, v, dt);
    Quat qNew = extrapolateOrientation(q, w, dt);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nPose extrapolee :\n";
    std::cout << "Position   : " << pNew.x << "  " << pNew.y << "  " << pNew.z << "\n";
    std::cout << "Quaternion : " << qNew.x << "  " << qNew.y << "  " << qNew.z << "  " << qNew.w << "\n";

    return 0;
}
```
