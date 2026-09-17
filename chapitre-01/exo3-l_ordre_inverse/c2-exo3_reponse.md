# Exercice, L'Ordre Inversé

## Énoncé

Reprenons l'exercice précédent et écrivons une seconde fonction qui applique la translation d'abord et la rotation ensuite.

Affichons les deux résultats pour le même point, puis trouvons une pose et un point pour lesquels les deux coïncident, et justifions pourquoi.

## Données

Soit une pose définie par une rotation R, représentée par un quaternion unitaire, et une translation t.

Soit p un point de l'espace.

Deux fonctions sont possibles :

f1(p) = R(p) + t, rotation puis translation.

f2(p) = R(p + t), translation puis rotation.

## Démonstration

On a, par linéarité de la rotation R (une rotation est une application linéaire orthogonale) :

R(p + t) = R(p) + R(t)

Donc :

f2(p) = R(p) + R(t)

En comparant avec f1(p) = R(p) + t, on obtient :

f1(p) = f2(p) si et seulement si R(t) = t

Cette condition ne porte que sur la pose, jamais sur le point p : t doit être invariant par la rotation R, c'est à dire que t doit être porté par l'axe de rotation lui même.

## Calcul numérique

Pour le vecteur (0.4, 0.6, 1), avec la pose constituée de la position (-1, 0, 2) et du quaternion (0.1221, 0.4517, -0.4945, -0.7325), on a :

Rotation puis translation, f1(p) :

    X : -2.1098
    Y : 0.3547
    Z : 2.4031

Translation puis rotation, f2(p) :

    X : -2.7777
    Y : -1.0157
    Z : 0.9864

Ainsi f1(p) et f2(p) diffèrent, ce qui est cohérent avec la démonstration précédente puisque rien n'indique que t = (-1, 0, 2) soit invariant par la rotation donnée.

## Cas de coïncidence

Pour que R(t) = t, choisissons t porté par l'axe de la rotation.

Prenons t = (0, 5, 0), translation le long de l'axe Y, et R le quaternion (0, 0.7071068, 0, 0.7071068), rotation de 90 degrés autour de l'axe Y.

Une rotation autour de Y laisse invariant tout vecteur porté par Y, donc R(t) = t est vérifié par construction.

Prenons un point quelconque, par exemple p = (2, 3, 4). On a alors :

    Entrez les coordonnees de la pose
    0
    5
    0
    Entrez les coordonnees du quaternion
    0
    0.7071068
    0
    0.7071068
    Entrez les coordonnees de la position actuelle
    2
    3
    4
    Rotation puis Translation :
    X : 4.0000
    Y : 8.0000
    Z : -2.0000

    Translation puis Rotation :
    X : 4.0000
    Y : 8.0000
    Z : -2.0000

## Conclusion

f1(p) = f2(p) pour ce couple (pose, point), et plus généralement pour tout point p dès que t est porté par l'axe de rotation. La condition R(t) = t est donc nécessaire et suffisante, et elle ne dépend que de la pose.

## Code

```cpp
#include <iostream>
#include <cmath>

struct Vec3 {
    double x, y, z;
};

struct Quaternion {
    double x, y, z, w;
};

Vec3 add(const Vec3& a, const Vec3& b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 scale(const Vec3& v, double s) {
    return { v.x * s, v.y * s, v.z * s };
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return { a.y * b.z - a.z * b.y,
             a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x };
}

// v' = v + 2 * w * (qv x v) + 2 * (qv x (qv x v))
Vec3 rotate(const Quaternion& q, const Vec3& v) {
    Vec3 qv = { q.x, q.y, q.z };
    Vec3 t = scale(cross(qv, v), 2.0);
    return add(add(v, scale(t, q.w)), cross(qv, t));
}

struct Pose {
    Vec3 position;
    Quaternion rotation;
};

Vec3 rotationPuisTranslation(const Pose& pose, const Vec3& p) {
    return add(rotate(pose.rotation, p), pose.position);
}

Vec3 translationPuisRotation(const Pose& pose, const Vec3& p) {
    return rotate(pose.rotation, add(p, pose.position));
}

void afficher(const std::string& titre, const Vec3& v) {
    std::cout << titre << "\n";
    std::cout << "X : " << v.x << "\n";
    std::cout << "Y : " << v.y << "\n";
    std::cout << "Z : " << v.z << "\n";
}

int main() {
    Pose pose;
    std::cout << "Entrez les coordonnees de la pose\n";
    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;
    std::cout << "Entrez les coordonnees du quaternion\n";
    std::cin >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z >> pose.rotation.w;

    Vec3 p;
    std::cout << "Entrez les coordonnees de la position actuelle\n";
    std::cin >> p.x >> p.y >> p.z;

    Vec3 r1 = rotationPuisTranslation(pose, p);
    Vec3 r2 = translationPuisRotation(pose, p);

    afficher("Rotation puis Translation :", r1);
    afficher("Translation puis Rotation :", r2);

    return 0;
}
```
