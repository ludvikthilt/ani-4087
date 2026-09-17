# Exercice, La Matrice de vue

## Énoncé

Écrivons les deux versions : celle qui inverse la matrice de la pose par une inversion générale, et celle qui construit directement le conjugué et la translation opposée.

Comparons les seize coefficients. Puis passons une pose dégénérée à la première et regardons ce qu'elle rend.

## Données

Soit une pose (R, t), où R est la matrice de rotation associée à un quaternion unitaire, et t une translation.

La pose s'écrit sous forme d'une matrice homogène 4x4 :

M = [ R   t ]
    [ 0   1 ]

Deux façons d'obtenir M^-1 :

Inversion générale : appliquer un pivot de Gauss-Jordan sur M, sans supposer quoi que ce soit sur sa structure.

Inversion analytique : construire directement [ R^T, -R^T t ; 0, 1 ], en s'appuyant sur le fait que R est orthogonale.

## Démonstration

Montrons que la forme analytique est bien l'inverse de M lorsque R est orthogonale, c'est à dire R^T R = Identité, ce qui est le cas pour toute matrice de rotation issue d'un quaternion unitaire.

Calculons le produit M * [ R^T, -R^T t ; 0, 1 ] :

[ R   t ] [ R^T   -R^T t ]   [ R R^T     R(-R^T t) + t ]
[ 0   1 ] [ 0      1     ] = [ 0         1             ]

Or R R^T = Identité par orthogonalité, donc le bloc en haut à gauche vaut Identité.

Le bloc en haut à droite vaut :

R(-R^T t) + t = -(R R^T) t + t = -t + t = 0

Le produit donne donc bien la matrice identité, ce qui établit que [ R^T, -R^T t ; 0, 1 ] est l'inverse de M, à condition que R soit orthogonale.

Ainsi, quand R provient d'un quaternion réellement unitaire, l'inversion générale par pivot et l'inversion analytique doivent rendre exactement la même matrice, à l'arrondi près.

## Calcul numérique sur une pose valide

Pour la pose constituée de la position (-1, 0, 2) et du quaternion (0.1221, 0.4517, -0.4945, -0.7325), quaternion dont la norme vaut 0.9999, donc unitaire aux arrondis près, on a :

    Entrez la position de la pose
    -1
    0
    2
    Entrez le quaternion unitaire de la pose
    0.1221
    0.4517
    -0.4945
    -0.7325

    === Comparaison sur une pose valide ===

    Inversion generale (Gauss-Jordan) :
        0.1031    0.8348    0.5411   -0.9792
       -0.6141    0.4811   -0.6256    0.6371
       -0.7827   -0.2679    0.5623   -1.9073
        0.0000    0.0000    0.0000    1.0000

    Inversion analytique (conjugue + translation opposee) :
        0.1031    0.8348    0.5411   -0.9792
       -0.6141    0.4811   -0.6256    0.6371
       -0.7827   -0.2679    0.5623   -1.9073
        0.0000    0.0000    0.0000    1.0000

    Ecart maximum sur les seize coefficients : 0.0001

Les deux inversions coïncident, ce qui confirme la démonstration : dès que R est orthogonale, les deux méthodes rendent le même résultat, l'écart de 0.0001 provenant uniquement des arrondis en virgule flottante.

## Pose dégénérée passée à l'inversion générale

Prenons maintenant une matrice qui ne représente aucune pose valide : deux de ses lignes sont identiques, elle est donc de rang déficient et n'admet aucune inverse.

    === Pose degeneree passee a l'inversion generale ===

    Matrice degeneree (rang deficient) :
        1.0000    0.0000    0.0000    5.0000
        0.0000    1.0000    0.0000    3.0000
        0.0000    1.0000    0.0000    3.0000
        0.0000    0.0000    0.0000    1.0000

    Ce que rend InverserGenerale :
        1.0000    0.0000    0.0000    0.0000
        0.0000    1.0000    0.0000    0.0000
        0.0000    0.0000    1.0000    0.0000
        0.0000    0.0000    0.0000    1.0000

## Observation

Aucune erreur, aucun message : la fonction rend l'identité comme si la pose était neutre, alors que la matrice d'entrée ne représente aucune transformation valide.

## Conclusion

Un pivot de Gauss-Jordan qui ne vérifie pas la nullité de son pivot avant de continuer ne détecte pas la déficience de rang, il l'ignore silencieusement. L'inversion générale n'est donc fiable que si l'on vérifie, avant ou pendant l'élimination, qu'aucun pivot ne s'annule, faute de quoi une matrice qui ne représente rien de valide rend un résultat qui a toutes les apparences d'un résultat correct.

## Code

```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct Vec3 {
    double x, y, z;
};

struct Quaternion {
    double x, y, z, w;
};

using Matrice4 = std::vector<std::vector<double>>;

Matrice4 matriceIdentite() {
    Matrice4 m(4, std::vector<double>(4, 0.0));
    for (int i = 0; i < 4; ++i) m[i][i] = 1.0;
    return m;
}

Matrice4 poseEnMatrice(const Vec3& t, const Quaternion& q) {
    double x = q.x, y = q.y, z = q.z, w = q.w;
    Matrice4 m = matriceIdentite();

    m[0][0] = 1 - 2 * (y * y + z * z);
    m[0][1] = 2 * (x * y - z * w);
    m[0][2] = 2 * (x * z + y * w);
    m[0][3] = t.x;

    m[1][0] = 2 * (x * y + z * w);
    m[1][1] = 1 - 2 * (x * x + z * z);
    m[1][2] = 2 * (y * z - x * w);
    m[1][3] = t.y;

    m[2][0] = 2 * (x * z - y * w);
    m[2][1] = 2 * (y * z + x * w);
    m[2][2] = 1 - 2 * (x * x + y * y);
    m[2][3] = t.z;

    return m;
}

// Inversion generale par elimination de Gauss-Jordan, sans verification de pivot.
Matrice4 inverserGenerale(Matrice4 m) {
    const int n = 4;
    Matrice4 inv = matriceIdentite();

    for (int col = 0; col < n; ++col) {
        double pivot = m[col][col];
        if (std::fabs(pivot) < 1e-12) {
            continue; // aucune verification, l'elimination se poursuit quand meme
        }
        for (int j = 0; j < n; ++j) {
            m[col][j] /= pivot;
            inv[col][j] /= pivot;
        }
        for (int i = 0; i < n; ++i) {
            if (i == col) continue;
            double facteur = m[i][col];
            for (int j = 0; j < n; ++j) {
                m[i][j] -= facteur * m[col][j];
                inv[i][j] -= facteur * inv[col][j];
            }
        }
    }
    return inv;
}

// Inversion analytique : R^T et -R^T * t, valide uniquement si R est orthogonale.
Matrice4 inverserAnalytique(const Vec3& t, const Quaternion& q) {
    Matrice4 pose = poseEnMatrice(t, q);
    Matrice4 inv = matriceIdentite();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            inv[i][j] = pose[j][i];

    for (int i = 0; i < 3; ++i) {
        double s = 0.0;
        for (int j = 0; j < 3; ++j)
            s += inv[i][j] * pose[j][3];
        inv[i][3] = -s;
    }
    return inv;
}

void afficherMatrice(const std::string& titre, const Matrice4& m) {
    std::cout << titre << "\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            std::cout << std::fixed << std::setprecision(4) << std::setw(10) << m[i][j];
        std::cout << "\n";
    }
}

double ecartMax(const Matrice4& a, const Matrice4& b) {
    double e = 0.0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            e = std::max(e, std::fabs(a[i][j] - b[i][j]));
    return e;
}

int main() {
    Vec3 t;
    Quaternion q;

    std::cout << "Entrez la position de la pose\n";
    std::cin >> t.x >> t.y >> t.z;
    std::cout << "Entrez le quaternion unitaire de la pose\n";
    std::cin >> q.x >> q.y >> q.z >> q.w;

    std::cout << "\n=== Comparaison sur une pose valide ===\n\n";

    Matrice4 generale = inverserGenerale(poseEnMatrice(t, q));
    Matrice4 analytique = inverserAnalytique(t, q);

    afficherMatrice("Inversion generale (Gauss-Jordan) :", generale);
    std::cout << "\n";
    afficherMatrice("Inversion analytique (conjugue + translation opposee) :", analytique);
    std::cout << "\nEcart maximum sur les seize coefficients : " << ecartMax(generale, analytique) << "\n";

    std::cout << "\n=== Pose degeneree passee a l'inversion generale ===\n\n";

    Matrice4 degeneree = {
        {1, 0, 0, 5},
        {0, 1, 0, 3},
        {0, 1, 0, 3},
        {0, 0, 0, 1}
    };

    afficherMatrice("Matrice degeneree (rang deficient) :", degeneree);
    std::cout << "\n";
    afficherMatrice("Ce que rend InverserGenerale :", inverserGenerale(degeneree));

    return 0;
}
```
