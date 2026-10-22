# Chapitre 6 — Exercice 2 : La dérive, provoquée

## Fichiers

- [derive.cpp](derive.cpp)
- [derive.txt](derive.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Résultat reproductible du modèle

Le défaut étudié réapplique le dernier delta brut lu à chaque image. Pour quantifier ce comportement sans prétendre avoir mesuré une souris réelle, le scénario consigné dans [derive.txt](derive.txt) fixe une sensibilité de 0,1 degré/pixel, un delta résiduel de 2 pixels/image et 120 images/s. La vitesse résultante est donc `2 × 0,1 × 120 = 24 deg/s`.

| t (s) | Images à 120 Hz | Delta réutilisé (pixels/image) | Lacet calculé |
|---:|---:|---:|---:|
| 3 | 360 | 2 | 72° |
| 4 | 480 | 2 | 96° |
| 5 | 600 | 2 | 120° |
| 6 | 720 | 2 | 144° |
| 7 | 840 | 2 | 168° |

Il s’agit d’un scénario analytique reproductible avec le facteur du programme, et non d’un relevé de capteur. Le programme de saisie actuel ne reçoit pas d’événements Windows/R3D ; aucune valeur ne doit donc être interprétée comme une mesure physique.

## Réponses

- **Sensibilité du scénario :** 0,1 degré/pixel.
- **Vitesse de dérive du scénario :** 24 degrés/seconde.
- **Calcul :** la pente du lacet est `(168 − 72) / (7 − 3) = 24 deg/s`.
- **Cause :** le delta du dernier événement n’est pas consommé/remis à zéro. Le code le multiplie par la sensibilité à chaque image, même quand aucun nouveau mouvement n’a lieu.
- **Correction :** traiter les deltas comme des événements par image, les additionner s’il y en a plusieurs, puis remettre l’accumulateur à zéro après consommation.

Les lignes et leur statut de simulation sont conservés dans [derive.txt](derive.txt).
