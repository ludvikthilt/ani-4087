# Exercice - Les Trois Espaces Dessinés

## Énoncé
Sans écrire de code, dessinez sur une même feuille une pièce vue de côté, avec un utilisateur debout, et placez les origines des trois espaces.

Puis placez une table à quatre-vingts centimètres dans chacun des trois, et montrez où elle se retrouve. Rendez le dessin.

## Démonstration

### On a
Trois espaces de référence coexistent dans une expérience en réalité virtuelle.

L'espace monde, dont l'origine Ow est fixe et arbitraire, indépendante de la pièce et de l'utilisateur.

L'espace de suivi, ou espace pièce, dont l'origine Op est posée au sol, à l'endroit où l'utilisateur s'est tenu lors de l'étalonnage du système.

L'espace local, dont l'origine Ol est celle du casque, à hauteur des yeux, et qui se déplace et tourne avec la tête de l'utilisateur.

La table a une hauteur h = 0.80 m, mesurée depuis le sol de la pièce, sol commun à l'espace monde et à l'espace de suivi.

### Ainsi
Soit Hu la hauteur des yeux de l'utilisateur au dessus du sol, prise ici à 1.60 m pour un adulte debout.

Dans l'espace monde, le sol de la pièce est décalé de l'origine Ow d'une hauteur fixe d0 selon la position de la pièce dans le bâtiment. La table se trouve donc à :

y_monde = d0 + h

Dans l'espace de suivi, l'origine Op est elle-même posée au sol, donc d0 = 0 relativement à cette origine, et la table se trouve à :

y_pièce = h = 0.80 m

au dessus de l'origine, à la position horizontale mesurée depuis le point d'étalonnage.

Dans l'espace local, l'origine Ol est à hauteur des yeux, au dessus du sol, la table se trouve donc en dessous de cette origine d'une distance :

y_local = h - Hu = 0.80 - 1.60 = -0.80 m

et cette coordonnée locale tourne avec la tête, la table change donc de position relative dans cet espace à chaque rotation de l'utilisateur, alors qu'elle reste fixe dans les deux autres espaces.

### Conclusion
Vue de côté, la pièce et les trois origines se placent ainsi :

    Ow (monde) o - - - - - - - - - - - - - - - - - - -   (origine arbitraire, hors piece)
                          |
                          |  d0
                          |
    -------- sol -------- Op (pièce) -------------------
                          .                    ___
                          .                   |Tbl| h = 0.80 m au dessus du sol
                          .                   |___|
                          .
                       tête Ol (local, à Hu = 1.60 m, tourne avec l'utilisateur)
                          |
                        corps debout
                          |
    -------- sol ---------+-----------------------------

La table à 0.80 m se retrouve donc :
- dans l'espace monde, à la hauteur d0 + 0.80 m au dessus de Ow
- dans l'espace pièce, à la hauteur 0.80 m au dessus de Op
- dans l'espace local, à la hauteur -0.80 m sous Ol, et cette valeur tourne avec l'utilisateur

### Observation
La hauteur de la table reste constante dans l'espace monde et dans l'espace pièce, puisque ces deux origines sont fixes au sol. Seul l'espace local fait varier la position perçue de la table, du fait qu'il est attaché à la tête, en position comme en orientation. C'est précisément cette distinction qui impose de toujours exprimer les objets persistants de la scène dans l'espace pièce ou dans l'espace monde, et de ne convertir vers l'espace local qu'au moment du rendu.
