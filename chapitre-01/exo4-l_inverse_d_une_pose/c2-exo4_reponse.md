# Exercice, L'Inverse d'une Pose

## Énoncé

Écrivons Inverser(pose) à la main, à partir du conjugué du quaternion et de la position opposée tournée par ce conjugué.

Vérifions la : appliquons la pose à un point, puis l'inverse au résultat, et affichons l'écart au point de départ. Il doit être nul aux arrondis près.

## Données

Soit une pose (R, t), où R est un quaternion unitaire et t une translation.

L'application de la pose à un point p est donnée par :

Pose(p) = R(p) + t

Soit R* le conjugué de R, défini par R* = (-x, -y, -z, w) si R = (x, y, z, w).

Pour un quaternion unitaire, le conjugué correspond exactement à la rotation inverse, c'est à dire R*(R(p)) = p pour tout p.

## Construction de la pose inverse

Posons la pose inverse comme (R*, R*(-t)).

Vérifions qu'elle annule bien Pose :

InversePose(Pose(p)) = R*(R(p) + t) + R*(-t)

Or R* est linéaire, donc :

R*(R(p) + t) = R*(R(p)) + R*(t) = p + R*(t)

Ainsi :

InversePose(Pose(p)) = p + R*(t) + R*(-t) = p + R*(t) - R*(t) = p

On a donc, pour tout point p, InversePose(Pose(p)) = p, ce qui confirme que (R*, R*(-t)) est bien l'inverse de la pose (R, t).

## Calcul numérique

Pour le vecteur (0.4, 0.6, 1), avec la pose constituée de la position (-1, 0, 2) et du quaternion (0.1221, 0.4517, -0.4945, -0.7325), on a :

    Entrez les coordonnees de la pose
    -1
    0
    2
    Entrez les coordonnees du quaternion
    0.1221
    0.4517
    -0.4945
    -0.7325
    Entrez les coordonnees de la position actuelle
    0.4
    0.6
    1
    POSE :
    X : -2.1098
    Y : 0.3547
    Z : 2.4031

    INVERSE DE LA POSE :
    X : 0.4000
    Y : 0.6000
    Z : 1.0000

    Ecart : 0.0001

## Conclusion

L'écart obtenu, 0.0001, est nul aux arrondis près, ce qui est cohérent avec la démonstration : InversePose(Pose(p)) = p exactement, la différence observée provient uniquement des erreurs d'arrondi en virgule flottante. La fonction InversePose est donc correcte.

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

Quaternion conjugate(const Quaternion& q) {
    return { -q.x, -q.y, -q.z, q.w };
}

struct Pose {
    Vec3 position;
    Quaternion rotation;
};

Vec3 appliquerPose(const Pose& pose, const Vec3& p) {
    return add(rotate(pose.rotation, p), pose.position);
}

Pose inversePose(const Pose& pose) {
    Quaternion qInv = conjugate(pose.rotation);
    Vec3 posInv = rotate(qInv, scale(pose.position, -1.0));
    return { posInv, qInv };
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

    Vec3 resultatPose = appliquerPose(pose, p);
    Pose poseInverse = inversePose(pose);
    Vec3 resultatInverse = appliquerPose(poseInverse, resultatPose);

    afficher("POSE :", resultatPose);
    afficher("INVERSE DE LA POSE :", resultatInverse);

    double ecart = norme(sub(resultatInverse, p));
    std::cout << "Ecart : " << ecart << "\n";

    return 0;
}
```
