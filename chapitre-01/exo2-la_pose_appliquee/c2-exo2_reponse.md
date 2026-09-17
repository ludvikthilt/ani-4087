# Exercice 2, La Pose Appliquée

## Énoncé

Écrivez la structure Pose, avec une position et un quaternion, et la fonction qui applique une pose à un point, rotation puis translation.

Le quaternion est donné par ses quatre composantes, déjà normalisé. Votre programme lit une pose et un point, et affiche le point transformé.

## Démonstration

### On a

Une pose définie par une position t et un quaternion unitaire q = (x, y, z, w). Pour un vecteur v, la rotation par q se calcule sans passer par une matrice, par la formule fermée suivante, en notant qv = (x, y, z) la partie vectorielle du quaternion.

    v' = v + 2w (qv x v) + 2 qv x (qv x v)

Appliquer la pose à un point p signifie tourner puis translater.

    AppliquerPose(pose, p) = Rotation(q, p) + t

### Ainsi

Pour p = (0.4, 0.6, 1), t = (-1, 0, 2), q = (0.1221, 0.4517, -0.4945, -0.7325), on calcule d'abord le premier produit vectoriel.

    qv x p = (0.7484, -0.3199, -0.1074)

puis le second.

    qv x (qv x p) = (-0.2067, -0.3570, -0.3771)

et enfin la somme complète.

    Rotation(q, p) = p + 2w(qv x p) + 2 qv x (qv x p) = (-1.1099, 0.3547, 0.4031)

### Conclusion

En ajoutant la translation t, on obtient le point transformé.

    X : -2.1098
    Y :  0.3547
    Z :  2.4031

### Observation

Le résultat dépend de l'ordre choisi, rotation puis translation revient à tourner le point autour de l'origine du repère local avant de le replacer dans le monde. L'exercice suivant montre que l'ordre inverse donne, en général, un résultat différent.

## Code

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; };
struct Pose { Vec3 position; Quat rotation; };

Vec3 Add(const Vec3& a, const Vec3& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
Vec3 Scale(const Vec3& a, double s)    { return { a.x * s, a.y * s, a.z * s }; }

Vec3 Cross(const Vec3& a, const Vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 Tourner(const Quat& q, const Vec3& v) {
    Vec3 qv = { q.x, q.y, q.z };
    Vec3 c1 = Cross(qv, v);
    Vec3 c2 = Cross(qv, c1);
    return Add(v, Add(Scale(c1, 2.0 * q.w), Scale(c2, 2.0)));
}

Vec3 AppliquerPose(const Pose& pose, const Vec3& p) {
    return Add(Tourner(pose.rotation, p), pose.position);
}

int main() {
    Pose pose;
    cout << "Entrez la position de la pose\n";
    cin >> pose.position.x >> pose.position.y >> pose.position.z;

    cout << "Entrez le quaternion unitaire de la pose\n";
    cin >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z >> pose.rotation.w;

    Vec3 p;
    cout << "Entrez le point\n";
    cin >> p.x >> p.y >> p.z;

    Vec3 r = AppliquerPose(pose, p);

    cout << fixed << setprecision(4);
    cout << "X : " << r.x << "\n";
    cout << "Y : " << r.y << "\n";
    cout << "Z : " << r.z << "\n";

    return 0;
}
```
