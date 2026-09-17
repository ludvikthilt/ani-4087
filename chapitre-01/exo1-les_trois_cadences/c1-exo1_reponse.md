# Budget de temps par image en VR

## Enoncé

Calculer la durée d'une image à 72, 90 et 120 Hz, au dixième de milliseconde. Pour chacune, soustraire les 8 ms prises par les capteurs, la transmission, la composition et l'affichage, et donner le temps qu'il reste pour le code.

## Sachant que

- La durée d'une image = 1000 / fréquence (ms).
- 8 ms sont fixes, prises par le pipeline système avant que le code applicatif n'agisse :
  - **capteurs** : mesure de la position/orientation de la tête par le casque ;
  - **transmission** : transfert des données capteurs → ordinateur, puis image → écran ;
  - **composition** : assemblage des couches d'image par le système (reprojection incluse) ;
  - **affichage** : temps d'affichage effectif par l'écran (scan-out).

## On a

| Fréquence | Durée = 1000/F | − 8 ms | Reste pour le code |
|---|---|---|---|
| 72 Hz  | 1000/72 = 13,9 ms  | 13,9 − 8 | **5,9 ms** |
| 90 Hz  | 1000/90 = 11,1 ms  | 11,1 − 8 | **3,1 ms** |
| 120 Hz | 1000/120 = 8,3 ms  | 8,3 − 8  | **0,3 ms** |

| Fréquence | Durée d'image | − 8 ms (pipeline) | Reste pour le code |
|---|---|---|---|
| 72 Hz  | 13,9 ms | −8 ms | **5,9 ms** |
| 90 Hz  | 11,1 ms | −8 ms | **3,1 ms** |
| 120 Hz | 8,3 ms  | −8 ms | **0,3 ms** |

## Ainsi

- **72 Hz** : marge confortable, ~5,9 ms pour simuler et dessiner la scène.
- **90 Hz** : marge serrée, ~3,1 ms — il faut déjà optimiser sérieusement.
- **120 Hz** : marge quasi nulle, ~0,3 ms — le pipeline fixe (8 ms) mange presque tout le budget. À cette fréquence, soit le pipeline lui-même doit être compressé, soit le rendu doit être extrêmement léger (reprojection asynchrone, résolution réduite, etc.).
