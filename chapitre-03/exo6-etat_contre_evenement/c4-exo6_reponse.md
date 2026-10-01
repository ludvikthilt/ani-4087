# Chapitre 3 – Exercice 6 : État contre événement

> Dépôt : `ani-4087/chapitre-03/exo6-etat_contre_evenement/` · Fichier : `c4-exo6_reponse.md`

## 1. Énoncé

Ecrivons deux compteurs. Le premier s'incrémente à chaque image où la touche espace est tenue, lu par NkInput.IsKeydown. Le second s'incrément à chaque image où la touche escape est tenue , lu par NkInput.IsKeyDown le second s'incremente a chaque NkKeyPressEvent sur escape.

Nous obtenons deux nombres par deux méthodes différentes (l'une par lecture d'un **état**, l'autre par comptage d'**événements**), nous les rendons et nous expliquons l'écart.

## 2. Étapes de résolution

1. Identifier  `NkKeyPressEvent` et `NkInput.IsKeyDown`.
2. Écrire le programme qui produit les deux nombres sur la même série d'actions.
3. Exécuter un scénario **scripté et identique** à chaque essai (par ex. : appuyer N fois sur Espace à un rythme donné).
4. Relever les deux nombres et l'écart absolu et relatif.
5. Expliquer l'écart : un état ne voit que ce qui existe **au moment où on le lit**, un événement est enregistré même si l'état est revenu à sa valeur initiale entre deux lectures (hypothèse à confirmer par nos mesures).

## 0. Environnement de mesure (à remplir une seule fois par session)

| Élément | Valeur |
|---|---|
| Date / heure |30/09/2026 , 18h55 |
| OS + version | Win11 , 22H2|
| CPU / RAM |i7 7th / 16 Go |
| Compilateur |clang-mingw |
| Version de Jenga |2.8.4 |
| Écran : résolution / mise à l'échelle (DPI %) / fréquence | 3840 x 2160 / 282 DPI / 60Hz |
| Mode d'alimentation (secteur / batterie) | secteur |
| Applications lourdes ouvertes en fond ? | non|

## 4. Méthodologie de mesure

**Ce qu'on mesure** : l'écart entre deux comptages d'une même action.

- **Scénario reproductible** : nombre d'appuis N connu à l'avance (ex. N = 50), rythme imposé (métronome sonore). 
- **Fréquence de rendu** : relever le nombre d'images par seconde pendant l'essai (compteur dans la boucle), car elle influence le comptage par état.
- **n = 5 essais** par rythme. Deux rythmes minimum (lent, rapide).
- On rapporte : nombre attendu N, nombre par état, nombre par événements, écart, écart relatif (%).

**Traitement statistique** (voir [`../../mesures/stats.py`](../../mesures/stats.py)) :
`python ../../mesures/stats.py v1 v2 v3 ...` renvoie n, moyenne, médiane, écart-type (échantillon), min, max.
On rapporte toujours **moyenne ± écart-type (n = …)** et on signale toute valeur aberrante au lieu de la supprimer en silence.

## 5. Code source

- [`main.cpp`](src/main.cpp)

```cpp
int nkmain(const nkentseu::NkEntryState &state)
{
    nkentseu::NkWindowConfig config;
    config.title = "La Fenetre Nue";
    config.width = 1000;
    config.height = 720;

    nkentseu::NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    bool running = true;
    auto& stackEvent = nkentseu::NkEvents();

    int compteurEtat = 0;
    int compteurEvenement = 0;
    int numeroImage = 0;

    while (running) {
        ++numeroImage;

        // Voie evenement : tous les evenements en attente
        nkentseu::NkEvent* event;
        while ((event = stackEvent.PollEvent()) != nullptr) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }

            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);

                /*if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                    running = false;
                }*/

                CompterEvenement(keyEvent, compteurEvenement);
            }
        }

        // Voie etat : une seule lecture par image, hors de la boucle d'evenements
        CompterEtat(compteurEtat, numeroImage);
    }

    std::cout << "\nImages totales                       : " << numeroImage << std::endl;
    std::cout << "Compteur 1 (etat, IsKeyDown)         : " << compteurEtat << std::endl;
    std::cout << "Compteur 2 (evenement, KeyPressEvent): " << compteurEvenement << std::endl;

    return 0;
}
```



## 6. Résultats

| Rythme | N attendu | Nombre (état) | Nombre (événements) | Écart |
|---|---|---|---|---|
| Lent | 10| 10| (246.0000 ±  32.6113 ) | (236.0000 ±  32.6113 ) |
| Rapide |10 |10 |(292.0000 ± 22.8035 ) | (282.0000 ± 22.8035 )|

## 7. Analyse
L'écart vient de la fréquence à laquelle chaque compteur estt mis à jour. Le compteur etat s'incremente pour autantt d'image affiché que le temps que la touche passe enfoncée. et le secnd s'incremente au moment de l'appuie


