# Chapitre 6 — Exercice 10 : La projection à la main

## Fichiers

- [projection.cpp](projection.cpp)
- [ecarts.txt](ecarts.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Comparaison calculée

Le programme compare les matrices en stockage colonne-ligne (`mat[col][row]`) et affiche le plus grand écart par ligne. Pour le FOV symétrique de 70° avec un aspect 1280:720, les termes de décentrage s’annulent et la projection manuelle se réduit à la perspective symétrique : les quatre écarts sont nuls à l’arrondi six décimales. Pour les quatre angles asymétriques Quest `(-52°, 45°, 48°, -50°)`, le calcul analytique reproduit la même formule et les écarts sont également nuls.

Ces deux comparaisons sont autonomes ; le second test n’instancie pas `NkCamera3D` et ne constitue pas une validation moteur. La sortie détaillée est dans [ecarts.txt](ecarts.txt).

## Réponses

- Les termes `mat[2][0]` et `mat[2][1]` décentrent le frustum horizontalement et verticalement.
- Avec des limites symétriques, les sommes des tangentes opposées sont nulles et ces coefficients de décentrage disparaissent.
- `NkCamera3D::SetFovAsym` prend des demi-angles signés en radians et calcule leurs tangentes. La matrice du kit est indexée `mat[col][row]` ; la projection utilise les plans proche/lointain `0,05` et `100`.
- Dans l’exercice Quest, les angles restent asymétriques : les deux coefficients de décentrage sont donc en général non nuls.

Le calcul local vérifie la formule, mais une validation finale avec `NkMat4f::Perspective` et `NkCamera3D::GetProj()` nécessite la compilation cohérente du kit et un projet R3D fonctionnel.
