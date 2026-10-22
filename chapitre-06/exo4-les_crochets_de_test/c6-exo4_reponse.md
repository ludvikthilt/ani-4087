# Chapitre 6 — Exercice 4 : Les crochets de test

## Fichiers

- [tete.cpp](tete.cpp)
- [test.txt](test.txt)
- [reponse.txt](reponse.txt)
- [Salle de départ](../main.cpp)

## Résultat

Le programme permet d’exécuter les tests sans ouvrir de fenêtre lorsque `MASALLE_TEST=1`. Les trois cas ont été exécutés et les assertions ont réussi :

```text
neutre attendu (0.0, 0.0, -1.0) obtenu (-0.0, 0.0, -1.0) OK
yaw 90 attendu (-1.0, 0.0, 0.0) obtenu (-1.0, 0.0, -0.0) OK
pitch 30 attendu (0.0, 0.5, -0.9) obtenu (-0.0, 0.5, -0.9) OK
Code de sortie : 0
```

Le mode normal, sans `MASALLE_TEST`, affiche qu’il faut activer les tests et termine avec le code 0. Le journal est reproduit dans [test.txt](test.txt).

## Réponses

- **Repère :** la tête neutre regarde vers `−Z`, `+Y` est le haut ; le lacet positif de 90° tourne le regard vers `−X`, et le tangage positif augmente sa composante verticale.
- **Test discriminant :** le cas `yaw 90` attend `(-1, 0, 0)`. Inverser le signe du sinus du lacet fait échouer ce test, contrairement au cas neutre qui ne détecterait pas l’erreur.
- **Intérêt du test automatisé :** le test donne un verdict stable à chaque exécution et couvre précisément les poses et conventions de signe sans demander de reproduire une souris ou une pose à la main.

Le test porte sur la formule vectorielle isolée de l’exécutable ; il ne valide pas les données de pose issues du moteur dans une fenêtre R3D.
