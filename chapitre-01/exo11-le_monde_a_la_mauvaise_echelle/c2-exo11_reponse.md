# Exercice - Le Monde à la Mauvaise Echelle

## Énoncé
Écrivez un programme qui affiche les dimensions d'une salle et de son mobilier, multipliées par un facteur lu à l'entrée.

Faites décrire la salle à trois personnes pour trois facteurs différents, sans leur dire lequel, et notez leurs mots. Rendez les trois descriptions.

## Démonstration

### On a
Une salle de longueur L = 5.0 m, de largeur l = 4.0 m et de hauteur H = 3.50 m, sol au plafond.

Un mobilier de référence, dimensions réelles fixées indépendamment de la salle :

table 1.20 × 0.75 × 0.75 m, chaise 0.45 × 0.45 × 0.90 m, porte 0.90 × 0.05 × 2.00 m

Un facteur d'échelle e lu à l'entrée.

### Ainsi
Toute dimension d, qu'elle appartienne à la salle ou au mobilier, se transforme uniformément par le même facteur :

d' = d × e

Pour e = 2, la salle devient l' = 4.0 × 2 = 8.00 m de largeur, L' = 5.0 × 2 = 10.00 m de longueur, H' = 3.50 × 2 = 7.00 m de hauteur. La table devient 2.40 × 1.50 × 1.50 m, la chaise 0.90 × 0.90 × 1.80 m, la porte 1.80 × 0.10 × 4.00 m.

Pour e = 1, aucune dimension ne change, la salle et le mobilier retrouvent leurs valeurs de référence.

Le corps de l'utilisateur, lui, n'est jamais soumis à ce facteur e, ses proportions et sa perception du mètre restent constantes quelle que soit l'échelle affichée. C'est ce décalage entre l'échelle du monde virtuel et l'échelle du corps qui produit une perception faussée des dimensions.

### Conclusion
À l'échelle 2 :

    Salle a l'echelle 2 :
    Salle : 8.00 x 10.00 m, plafond a 7.00 m
    - Table : 2.40 x 1.50 x 1.50 m
    - Chaise : 0.90 x 0.90 x 1.80 m
    - Porte : 1.80 x 0.10 x 4.00 m

À l'échelle 1 :

    Salle a l'echelle 1 :
    Salle : 4.00 x 5.00 m, plafond a 3.50 m
    - Table : 1.20 x 0.75 x 0.75 m
    - Chaise : 0.45 x 0.45 x 0.90 m
    - Porte : 0.90 x 0.05 x 2.00 m

### Observation
Avec une échelle différente de un, la réalité ne peut pas être retransmise de façon effective, puisque le corps de l'utilisateur reste inchangé pendant que le monde virtuel change de dimensions. Le but de la réalité virtuelle étant une immersion dans un monde dont le corps du joueur est familier, cette divergence entre l'échelle affichée et l'échelle corporelle cause des incohérences sensorielles et perceptives, d'où l'usage strict du mètre réel dans la conception des scènes.

## Témoignages

### Simeon

Simeon a dit :

>Cette celle est cohérente à l'oeil. Le plafond est très haut. Elle me plait

### Marie-France

Marie-France a dit :

>Les dimensions m'ont l'air normales, je ne remarque rien de particulier. 

### Léonidas

Léonidas a dit :

> Cette salle est cool, elle est plus spacieuse que la mienne.

## Code

```cpp
#include <iostream>
#include <iomanip>

struct Piece {
    double longueur, largeur, hauteur;
};

struct Meuble {
    const char* nom;
    double x, y, z;
};

Piece scale(const Piece& p, double e) {
    return { p.longueur * e, p.largeur * e, p.hauteur * e };
}

Meuble scale(const Meuble& m, double e) {
    return { m.nom, m.x * e, m.y * e, m.z * e };
}

int main() {
    Piece salle;
    double e;

    std::cout << "Entrez la longueur de la salle, m\n";
    std::cin >> salle.longueur;

    std::cout << "Entrez la largeur de la salle, m\n";
    std::cin >> salle.largeur;

    std::cout << "Entrez la hauteur de la salle, m\n";
    std::cin >> salle.hauteur;

    std::cout << "Entrez le facteur d'echelle\n";
    std::cin >> e;

    Meuble table = scale({ "Table", 1.20, 0.75, 0.75 }, e);
    Meuble chaise = scale({ "Chaise", 0.45, 0.45, 0.90 }, e);
    Meuble porte = scale({ "Porte", 0.90, 0.05, 2.00 }, e);
    Piece salleScaled = scale(salle, e);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nSalle a l'echelle " << e << " :\n";
    std::cout << "Salle : " << salleScaled.largeur << " x " << salleScaled.longueur
              << " m, plafond a " << salleScaled.hauteur << " m\n";
    std::cout << "- " << table.nom << " : " << table.x << " x " << table.y << " x " << table.z << " m\n";
    std::cout << "- " << chaise.nom << " : " << chaise.x << " x " << chaise.y << " x " << chaise.z << " m\n";
    std::cout << "- " << porte.nom << " : " << porte.x << " x " << porte.y << " x " << porte.z << " m\n";

    return 0;
}
```
