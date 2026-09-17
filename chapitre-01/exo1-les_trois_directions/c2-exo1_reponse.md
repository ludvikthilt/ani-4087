# Exercice 1, Les Trois Directions

## Énoncé

Écrivez les trois fonctions qui fixent la convention une fois pour toutes, Avant(), Haut() et Droite(), qui rendent chacune un vecteur unitaire dans la convention du module.

Votre programme lit trois réels, les traite comme un point, et affiche son produit scalaire avec chacune des trois directions. Trois lignes, quatre décimales.

## Démonstration

### On a

Un repère orthonormé direct, l'axe Y pointant vers le haut, l'axe X vers la droite. Le regard d'un observateur placé à l'origine porte, par convention du module, vers les Z négatifs.

Ces trois choix fixent entièrement les trois vecteurs unitaires cherchés.

    Droite = (1, 0, 0)
    Haut   = (0, 1, 0)
    Avant  = (0, 0, -1)

### Ainsi

Pour un point p = (x, y, z), le produit scalaire avec chacun de ces trois vecteurs se réduit à une seule coordonnée de p, au signe près.

    p . Droite = x
    p . Haut   = y
    p . Avant  = -z

### Conclusion

Pour p = (0.4, 0.6, 1), on obtient directement les trois valeurs demandées.

    Avant  : -1.0000
    Haut   :  0.6000
    Droite :  0.4000

### Observation

Le signe négatif sur Avant vient uniquement de la convention retenue, Avant pointant vers -Z. Avec une autre convention, par exemple Avant = (0, 0, 1), le même point donnerait +1.0000. Le résultat d'un produit scalaire avec une direction fixe n'a donc de sens qu'une fois la convention posée.

## Code

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

struct Vec3 { double x, y, z; };

double Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Avant()  { return { 0.0, 0.0, -1.0 }; }
Vec3 Haut()   { return { 0.0, 1.0,  0.0 }; }
Vec3 Droite() { return { 1.0, 0.0,  0.0 }; }

int main() {
    Vec3 p;
    cin >> p.x >> p.y >> p.z;

    cout << fixed << setprecision(4);
    cout << "Avant : "  << Dot(p, Avant())  << "\n";
    cout << "Haut : "   << Dot(p, Haut())   << "\n";
    cout << "Droite : " << Dot(p, Droite()) << "\n";

    return 0;
}
```
