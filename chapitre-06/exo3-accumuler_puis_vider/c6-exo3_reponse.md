# Chapitre 6 — Exercice 3 : Accumuler, puis vider

## Fichiers

- [accumulation.cpp](accumulation.cpp)
- [trois.txt](trois.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Comparaison reproductible

Le banc fourni compare trois règles sur le même scénario simulé : 120 images de déplacement à 0,05 pixel/image, puis cinq images sans nouvel événement. La dernière valeur brute reste à 0,05 pixel dans la variante fautive, tandis que le cumul correct est vidé après chaque image. Le cumul non vidé conserve les 120 événements.

| Temps après le début (s) | Lecture du dernier delta (°) | Cumul lu puis vidé (°) | Cumul jamais vidé (°) |
|---:|---:|---:|---:|
| 1,0083 | 0,605 | 0,600 | 36,900 |
| 1,0167 | 0,610 | 0,600 | 37,500 |
| 1,0250 | 0,615 | 0,600 | 38,100 |
| 1,0333 | 0,620 | 0,600 | 38,700 |
| 1,0417 | 0,625 | 0,600 | 39,300 |

Ces nombres sont les calculs du scénario d’entrée synthétique, à 0,1 degré/pixel ; ils ne proviennent pas d’une souris physique. Le détail est dans [trois.txt](trois.txt).

## Symptôme, cause, preuve, correction

- **Symptôme :** après l’arrêt du mouvement, le lacet « lecture du dernier delta » continue d’augmenter ; le cumul jamais vidé dérive beaucoup plus vite.
- **Cause :** la dernière valeur brute est réutilisée, ou le cumul complet des anciens événements est ajouté de nouveau à chaque image.
- **Preuve :** dans les cinq lignes après l’arrêt, le cumul correctement vidé reste à 0,600°, alors que les deux variantes fautives augmentent.
- **Correction :** additionner tous les deltas reçus pendant l’image, appliquer ce total une seule fois, puis le remettre à zéro.

Le test est un banc déterministe ; l’intégration de `NkInput` dans Salle est nécessaire pour transformer ces nombres en relevés d’entrée matérielle.
