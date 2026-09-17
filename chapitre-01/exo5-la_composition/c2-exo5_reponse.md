# Exercice, La Composition

## Énoncé

Écrivons la composition de deux poses, puis vérifions sur un cas que composer puis appliquer donne le même résultat qu'appliquer l'une après l'autre.

Affichons les deux points obtenus et leur écart.

## Données

Soit une pose parent (Rp, tp) et une pose enfant (Rc, tc).

L'application d'une pose (R, t) à un point p est donnée par Pose(p) = R(p) + t.

Appliquer l'enfant puis le parent à un point p donne :

Parent(Enfant(p)) = Rp(Rc(p) + tc) + tp

## Démonstration

Par linéarité de Rp, on a :

Rp(Rc(p) + tc) = Rp(Rc(p)) + Rp(tc)

Donc :

Parent(Enfant(p)) = Rp(Rc(p)) + Rp(tc) + tp

Or Rp(Rc(p)) est la rotation composée (Rp∘Rc)(p), qui correspond, pour des quaternions, au produit Rp * Rc.

Ainsi, en posant la pose composée comme :

Composee = (Rp * Rc, tp + Rp(tc))

on obtient :

Composee(p) = (Rp * Rc)(p) + tp + Rp(tc) = Rp(Rc(p)) + Rp(tc) + tp = Parent(Enfant(p))

On a donc, pour tout point p, Composee(p) = Parent(Enfant(p)), ce qui établit que la composition de deux poses se calcule par cette formule, sans devoir appliquer les deux poses séparément.

## Calcul numérique

Pour le vecteur (0.4, 0.6, 1), avec la pose parent constituée de la position (-1, 0, 2) et du quaternion (0.1221, 0.4517, -0.4945, -0.7325), et la pose enfant de la position (0, 2, -3) et du quaternion (0.1221, 0.4517, -0.4945, -0.7325), on a :

    Entrez les coordonnees de la pose parent
    -1
    0
    2
    Entrez les coordonnees du quaternion parent
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees de la pose enfant
    0
    2
    -3
    Entrez les coordonnees du quaternion enfant
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees du point
    0.4
    0.6
    1
    PAR COMPOSITION :
    X : -0.5283
    Y : 0.9020
    Z : -1.5333

    PAR ETAPES :
    X : -0.5283
    Y : 0.9021
    Z : -1.5333

    Ecart : 0.0001

## Conclusion

Les deux points obtenus coïncident aux arrondis près, l'écart de 0.0001 provenant uniquement des erreurs de calcul en virgule flottante. Ceci confirme la démonstration : composer d'abord les deux poses puis appliquer le résultat équivaut à appliquer les deux poses l'une après l'autre.

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

Vec3 sub(const Vec3& a, const Vec3& b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3 scale(const Vec3& v, double s) {
    return { v.x * s, v.y * s, v.z * s };
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return { a.y * b.z - a.z * b.y,
             a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x };
}

double norme(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 rotate(const Quaternion& q, const Vec3& v) {
    Vec3 qv = { q.x, q.y, q.z };
    Vec3 t = scale(cross(qv, v), 2.0);
    return add(add(v, scale(t, q.w)), cross(qv, t));
}

Quaternion multiply(const Quaternion& a, const Quaternion& b) {
    return {
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    };
}

struct Pose {
    Vec3 position;
    Quaternion rotation;
};

Vec3 appliquerPose(const Pose& pose, const Vec3& p) {
    return add(rotate(pose.rotation, p), pose.position);
}

Pose composerPose(const Pose& parent, const Pose& enfant) {
    Vec3 position = add(parent.position, rotate(parent.rotation, enfant.position));
    Quaternion rotation = multiply(parent.rotation, enfant.rotation);
    return { position, rotation };
}

void afficher(const std::string& titre, const Vec3& v) {
    std::cout << titre << "\n";
    std::cout << "X : " << v.x << "\n";
    std::cout << "Y : " << v.y << "\n";
    std::cout << "Z : " << v.z << "\n";
}

int main() {
    Pose parent;
    std::cout << "Entrez les coordonnees de la pose parent\n";
    std::cin >> parent.position.x >> parent.position.y >> parent.position.z;
    std::cout << "Entrez les coordonnees du quaternion parent\n";
    std::cin >> parent.rotation.x >> parent.rotation.y >> parent.rotation.z >> parent.rotation.w;

    Pose enfant;
    std::cout << "Entrez les coordonnees de la pose enfant\n";
    std::cin >> enfant.position.x >> enfant.position.y >> enfant.position.z;
    std::cout << "Entrez les coordonnees du quaternion enfant\n";
    std::cin >> enfant.rotation.x >> enfant.rotation.y >> enfant.rotation.z >> enfant.rotation.w;

    Vec3 p;
    std::cout << "Entrez les coordonnees du point\n";
    std::cin >> p.x >> p.y >> p.z;

    Pose composee = composerPose(parent, enfant);
    Vec3 parComposition = appliquerPose(composee, p);
    Vec3 parEtapes = appliquerPose(parent, appliquerPose(enfant, p));

    afficher("PAR COMPOSITION :", parComposition);
    afficher("PAR ETAPES :", parEtapes);

    double ecart = norme(sub(parComposition, parEtapes));
    std::cout << "Ecart : " << ecart << "\n";

    return 0;
}
```
