# Demo 3 : Le tour complet à l'envers

## Énoncé
Montrer la vitesse angulaire sans forçage du chemin court, sur un delta minuscule qui se lit comme un tour presque complet, puis ajouter les trois lignes et remontrer.

## On a
Soit $\theta_{\text{avant}} = 359{,}9°$ et $\theta_{\text{après}} = 0{,}1°$ (passage par 0°), sur $\Delta t = 0{,}1\,$s.

**Version avec forçage du chemin court (fausse) :**
$$\Delta\theta_{\text{brut}} = 0{,}1 - 359{,}9 = -359{,}8°$$
$$
\Delta\theta_{\text{forcé}} = ((\Delta\theta_{\text{brut}} + 180°) \bmod 360°) - 180° = +0{,}2°$$
$$\omega_{\text{faux}} = \frac{+0{,}2°}{0{,}1\,\text{s}} = +2°/\text{s} \quad (\text{sens positif})$$

**Version sans forçage (correcte) :**
$$\omega_{\text{vrai}} = \frac{\Delta\theta_{\text{brut}}}{\Delta t} = \frac{-359{,}8°}{0{,}1\,\text{s}} = -3598°/\text{s}$$
Le delta minuscule en lecture ($0{,}2°$) est en réalité un **tour presque complet dans le sens négatif** ($-359{,}8°$).

**Les trois lignes à ajouter :**
```python
delta = theta_apres - theta_avant          # 1. delta brut, non replié
if abs(delta) > 180.0:                     # 2. détection d'un tour quasi complet
    omega = delta / dt                     # 3. vitesse signée réelle, sans wrap
```

## Ainsi
$$\underbrace{\omega = \frac{+0{,}2°}{\Delta t}}_{\text{forçage : faux}} \neq \underbrace{\omega = \frac{-359{,}8°}{\Delta t}}_{\text{brut : vrai}}$$

Le repliement vers le chemin court ($[-180°, 180°]$) détruit l'information du nombre de tours : il rend un mouvement rapide en un mouvement lent de sens opposé.

## Conclusion
Pour mesurer une vitesse angulaire, il faut conserver le delta **brut et signé**. Forcer le chemin court ($((\Delta\theta + 180°) \bmod 360°) - 180°$) est correct pour une orientation, mais faux pour une vitesse : un delta de $-359{,}8°$ devient $+0{,}2°$ et la vitesse réelle ($-3598°/\text{s}$) est masquée.

## Observation
Une grandeur **instantanée** (position, orientation) tolère le repliement ; une grandeur **dérivée** (vitesse, accélération) l'interdit, car elle est sensible à la variation totale, pas à sa représentation. Confondre les deux donne des objets qui « tournent doucement à l'envers » alors qu'ils effectuent un tour rapide, visible dans un casque comme une saccade inexpliquée.
