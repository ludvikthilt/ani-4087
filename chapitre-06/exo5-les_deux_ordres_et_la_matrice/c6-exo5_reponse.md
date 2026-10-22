# Chapitre 6 — Exercice 5 : Les deux ordres, et la matrice

## Fichiers

- [ordres.cpp](ordres.cpp)
- [regards.txt](regards.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Résultat calculé (lacet 45°, tangage 30°)

```text
qYaw*qPitch: (-0.6124, 0.5000, -0.6124)
qPitch*qYaw: (-0.7071, 0.3536, -0.6124)
RotationY*RotationX: (-0.6124, 0.5000, -0.6124)
```

Le vecteur de départ est l’avant de la salle `(0, 0, -1)`. Les résultats sont aussi consignés dans [regards.txt](regards.txt).

## Réponses

- `RotationY(yaw) * RotationX(pitch)` rejoint le regard obtenu avec `qYaw * qPitch` dans cette convention. La multiplication n’est pas commutative : `qPitch * qYaw` donne un autre regard.
- L’ordre retenu est lacet puis tangage. Inverser ces opérations change le résultat spatial ; les deux transformations ne sont donc pas interchangeables.
- Ce résultat vient du programme autonome en double précision. Il vérifie la convention algébrique, mais ne constitue pas une comparaison exécutée entre les types `NkQuatf` et `NkMat4f` du kit.

La comparaison numérique moteur reste distincte de la vérification locale et ne doit pas être présentée comme une mesure graphique.
