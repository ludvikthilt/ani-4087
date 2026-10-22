# Chapitre 6 — Exercice 7 : Le coût mesuré

## Fichiers

- [cout.cpp](cout.cpp)
- [MaSalle.jenga](MaSalle.jenga)
- [mesures.txt](mesures.txt)
- [reponse.txt](reponse.txt)

## Mesures exécutées

Chaque durée correspond à 1 000 000 d’itérations. Les trois exécutions par méthode ont une dispersion importante ; la médiane est donc également indiquée.

| Configuration | Méthode | Runs (ms) | Moyenne (ms) | Médiane (ms) | Médiane par itération |
|---|---|---|---:|---:|---:|
| Debug | Matrices puis conversion | 206,149 ; 184,151 ; 128,742 | 173,014 | 184,151 | 184,2 ns |
| Debug | Produit de quaternions | 75,371 ; 89,198 ; 114,515 | 93,028 | 89,198 | 89,2 ns |
| Release | Matrices puis conversion | 73,910 ; 56,118 ; 86,528 | 72,185 | 73,910 | 73,9 ns |
| Release | Produit de quaternions | 62,450 ; 125,279 ; 73,217 | 86,982 | 73,217 | 73,2 ns |

Les mesures détaillées sont conservées dans [mesures.txt](mesures.txt). À 90 Hz, le budget par image est d’environ 11,11 ms ; ces mesures d’une opération de boucle ne sont pas le temps de rendu complet d’une image.

## Réponses et limites

- En Debug, la médiane des quaternions est plus basse (89,2 ns contre 184,2 ns). En Release, les médianes sont presque identiques (73,2 ns contre 73,9 ns).
- Les dispersions — surtout le run Release quaternion à 125,279 ms — sont assez fortes pour rendre une conclusion générale fragile.
- Le programme mesure des opérations autonomes en `double`, pas les primitives exactes `NkMat4f`/`NkQuatf` utilisées dans Salle. Ce résultat ne justifie donc pas à lui seul un choix de moteur.
- Le coût médian par opération représente environ 0,0017 % du budget de 11,11 ms en Debug matrices et 0,0007 % en Release. Il ne comprend ni le reste de la logique ni le rendu.

Il faudrait chronométrer les deux chemins Nkentseu, dans une même configuration Release et avec une répétition plus longue/plus nombreuse, avant d’optimiser ce choix. `MaSalle.jenga` contient le profil Release avec optimisation pour la vitesse.
