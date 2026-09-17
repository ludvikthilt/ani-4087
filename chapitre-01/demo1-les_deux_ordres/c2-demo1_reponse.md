# Démonstration — Demo 1 : Les deux ordres

## Énoncé
Montrer, en partant du même point, que « je tourne puis j'avance » et « j'avance puis je tourne » donnent deux résultats différents, puis montrer les deux résultats du programme.

## On a
Soit le point de départ $P_0$, une rotation de centre $P_0$ et d'angle $\theta$ (matrice $R(\theta)$), et un vecteur de translation $\vec{v}$.

**Ordre 1 — « je tourne puis j'avance » :**
$$P_1 = R(\theta)\,P_0 + \vec{v}$$

**Ordre 2 — « j'avance puis je tourne » :**
$$P_2 = R(\theta)\,(P_0 + \vec{v}) = R(\theta)\,P_0 + R(\theta)\,\vec{v}$$

## Ainsi
$$P_1 - P_2 = \vec{v} - R(\theta)\,\vec{v} = \bigl(I - R(\theta)\bigr)\,\vec{v}$$

Or $P_1 = P_2 \iff \bigl(I - R(\theta)\bigr)\,\vec{v} = \vec{0}$, c'est-à-dire :
- $\vec{v} = \vec{0}$ (on n'avance pas), ou
- $\theta \equiv 0 \pmod{2\pi}$ (on ne tourne pas).

Dans tous les autres cas, $(I - R(\theta))$ est inversible (ses valeurs propres sont $1 - e^{\pm i\theta} \neq 0$), donc $P_1 \neq P_2$.

**Résultat du programme :**
- tourne(90°) puis avance(1) : $P_1 = (0,0) + (1,0) = (1,0)$
- avance(1) puis tourne(90°) : $P_2 = R(90°)\,(1,0) = (0,1)$

## Conclusion
$(1,0) \neq (0,1)$ : la composition de transformations rigides **n'est pas commutative**. L'ordre « tourner puis avancer » et l'ordre « avancer puis tourner » produisent des positions finales distinctes dès que $\theta \not\equiv 0$ et $\vec{v} \neq \vec{0}$.

## Observation
Comme la multiplication des matrices n'est pas commutative en général ($AB \neq BA$), tout enchaînement de mouvements dans un espace (robot, personnage, caméra) dépend de l'ordre des opérations. Deux instructions permutées modifient la trajectoire, même avec les mêmes paramètres et le même point de départ, c'est une source classique de bugs d'animation.
