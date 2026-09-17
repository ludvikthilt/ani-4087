# Exercice, Le bras, en pose

## Énoncé

Construisons un bras articulé à trois segments : une épaule à l'origine, un coude à un bras de distance, une main à un avant-bras du coude.

Chaque articulation porte sa pose dans le repère de la précédente, et la pose d'une articulation dans le monde s'obtient en composant celle de son parent avec la sienne.

Affichons la position du coude et celle de la main dans l'espace du monde. Faisons tourner l'épaule et vérifions que la main suit.

## Données

Soit L1 la longueur du bras et L2 la longueur de l'avant-bras.

Soit trois poses locales :

Épaule, dans le monde : (0, 0, 0), rotation Rs.

Coude, dans le repère de l'épaule : (L1, 0, 0), rotation identité.

Main, dans le repère du coude : (L2, 0, 0), rotation identité.

D'après l'exercice précédent, la composition de deux poses (Rp, tp) et (Rc, tc) est (Rp * Rc, tp + Rp(tc)).

## Démonstration

Pose du coude dans le monde :

Coude_monde = Épaule_monde ∘ Coude_local = (Rs, (0,0,0)) ∘ (Identité, (L1,0,0))

D'où :

Coude_monde = (Rs, Rs((L1,0,0)))

La position du coude dans le monde est donc Rs((L1,0,0)), et sa rotation dans le monde est Rs.

Pose de la main dans le monde :

Main_monde = Coude_monde ∘ Main_locale = (Rs, Rs((L1,0,0))) ∘ (Identité, (L2,0,0))

D'où :

Main_monde = (Rs, Rs((L1,0,0)) + Rs((L2,0,0)))

La position de la main dans le monde est donc Rs((L1,0,0)) + Rs((L2,0,0)).

## Conservation des longueurs

Une rotation R conserve la norme de tout vecteur, c'est à dire |R(v)| = |v| pour tout v, puisque R est une transformation orthogonale.

Donc, avant comme après rotation de l'épaule :

|Coude_monde - Épaule_monde| = |Rs((L1,0,0))| = |(L1,0,0)| = L1

|Main_monde - Coude_monde| = |Rs((L2,0,0))| = |(L2,0,0)| = L2

Les deux longueurs restent donc égales à L1 et L2, quelle que soit la rotation appliquée à l'épaule.

## Calcul numérique

Pour une longueur de bras de 0.3 m, un avant-bras de 0.25 m, et un quaternion de l'épaule (0.1221, 0.4517, -0.4945, -0.7325), on a :

    --- Bras au repos ---
    Coude : 0.3000  0.0000  0.0000
    Main  : 0.5500  0.0000  0.0000

    Entrez le quaternion de rotation de l'epaule (qx qy qz qw)
    0.1221
    0.4517
    -0.4945
    -0.7325

    --- Apres rotation de l'epaule ---
    Coude : 0.0309  0.2504  0.1623
    Main  : 0.0566  0.4591  0.2975

    --- Verification (longueurs conservees) ---
    Epaule-Coude  avant : 0.3000   apres : 0.3000
    Coude-Main    avant : 0.2500   apres : 0.2500

## Conclusion

Les longueurs Épaule-Coude et Coude-Main restent inchangées avant et après rotation, ce qui confirme la démonstration : une rotation ne modifie jamais la norme d'un vecteur. Le coude et la main suivent bien le mouvement de l'épaule, puisque leurs poses dans le monde sont obtenues par composition avec la pose de l'épaule, tout en conservant les distances qui les séparent.

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

Pose composerPose(const Pose& parent, const Pose& enfant) {
    Vec3 position = add(parent.position, rotate(parent.rotation, enfant.position));
    Quaternion rotation = multiply(parent.rotation, enfant.rotation);
    return { position, rotation };
}

Quaternion identite() {
    return { 0.0, 0.0, 0.0, 1.0 };
}

int main() {
    double L1 = 0.3;
    double L2 = 0.25;

    Pose epaule = { {0.0, 0.0, 0.0}, identite() };
    Pose coudeLocal = { {L1, 0.0, 0.0}, identite() };
    Pose mainLocale = { {L2, 0.0, 0.0}, identite() };

    Pose coudeMonde = composerPose(epaule, coudeLocal);
    Pose mainMonde = composerPose(coudeMonde, mainLocale);

    std::cout << "--- Bras au repos ---\n";
    std::cout << "Coude : " << coudeMonde.position.x << "  " << coudeMonde.position.y << "  " << coudeMonde.position.z << "\n";
    std::cout << "Main  : " << mainMonde.position.x << "  " << mainMonde.position.y << "  " << mainMonde.position.z << "\n\n";

    double distEpauleCoudeAvant = norme(sub(coudeMonde.position, epaule.position));
    double distCoudeMainAvant = norme(sub(mainMonde.position, coudeMonde.position));

    Quaternion rotationEpaule;
    std::cout << "Entrez le quaternion de rotation de l'epaule (qx qy qz qw)\n";
    std::cin >> rotationEpaule.x >> rotationEpaule.y >> rotationEpaule.z >> rotationEpaule.w;

    epaule.rotation = rotationEpaule;

    Pose coudeMondeApres = composerPose(epaule, coudeLocal);
    Pose mainMondeApres = composerPose(coudeMondeApres, mainLocale);

    std::cout << "\n--- Apres rotation de l'epaule ---\n";
    std::cout << "Coude : " << coudeMondeApres.position.x << "  " << coudeMondeApres.position.y << "  " << coudeMondeApres.position.z << "\n";
    std::cout << "Main  : " << mainMondeApres.position.x << "  " << mainMondeApres.position.y << "  " << mainMondeApres.position.z << "\n";

    double distEpauleCoudeApres = norme(sub(coudeMondeApres.position, epaule.position));
    double distCoudeMainApres = norme(sub(mainMondeApres.position, coudeMondeApres.position));

    std::cout << "\n--- Verification (longueurs conservees) ---\n";
    std::cout << "Epaule-Coude  avant : " << distEpauleCoudeAvant << "   apres : " << distEpauleCoudeApres << "\n";
    std::cout << "Coude-Main    avant : " << distCoudeMainAvant << "   apres : " << distCoudeMainApres << "\n";

    return 0;
}
```
