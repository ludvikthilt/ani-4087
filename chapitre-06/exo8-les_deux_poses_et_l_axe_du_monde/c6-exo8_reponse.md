# Chapitre 6 — Exercice 8 : Les deux poses, et l’axe du monde

## Fichiers

- [poses.cpp](poses.cpp)
- [poses.txt](poses.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Résultats calculés

La position de la tête est `(0,30 ; 1,70 ; 1,20) m` et l’écart interpupillaire vaut 63 mm. Le calcul applique la pose à l’axe local `−X` pour construire `Right()` ; l’en-tête NkQuat du kit confirme cette convention.

| Pose | Œil gauche, axe tête (m) | Œil droit, axe tête (m) | Œil gauche, axe monde (m) | Œil droit, axe monde (m) | Écart gauche |
|---|---|---|---|---|---:|
| Neutre | (0,2685 ; 1,7000 ; 1,2000) | (0,3315 ; 1,7000 ; 1,2000) | (0,3315 ; 1,7000 ; 1,2000) | (0,2685 ; 1,7000 ; 1,2000) | 63,00 mm |
| Roulis 30° | (0,2727 ; 1,6843 ; 1,2000) | (0,3273 ; 1,7158 ; 1,2000) | (0,3315 ; 1,7000 ; 1,2000) | (0,2685 ; 1,7000 ; 1,2000) | 60,85 mm |
| Lacet 90° | (0,3000 ; 1,7000 ; 1,2315) | (0,3000 ; 1,7000 ; 1,1685) | (0,3315 ; 1,7000 ; 1,2000) | (0,2685 ; 1,7000 ; 1,2000) | 44,55 mm |

Ce sont les valeurs calculées par l’exécutable local, non un relevé d’un casque. Les positions complètes sont dans [poses.txt](poses.txt).

## Réponses

- Pour la tête neutre, les deux méthodes placent les yeux sur la même ligne horizontale ; toutefois, le signe de l’axe `Right() = −X` signifie que les étiquettes gauche/droite du calcul local sont inversées par rapport à l’axe monde `+X`.
- En roulis, la droite de la tête acquiert une composante verticale. En lacet de 90°, elle pointe selon Z, tandis que l’axe monde reste fixe sur X.
- Décaler les yeux le long d’un axe monde fixe plutôt que le long de la tête modifie leur position relative quand la tête pivote. L’effet de confort réel ne peut être conclu que par une observation dans un casque.

Le résultat expose donc aussi une incohérence de convention à résoudre dans Salle : le côté appelé « gauche » doit être défini de manière cohérente avec `Right()`.
