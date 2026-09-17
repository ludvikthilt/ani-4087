# Démonstration — Demo 2 : L'inversion qui ment

## Énoncé
Montrer une inversion générale qui rend l'identité sur une matrice dégénérée sans le moindre message, imaginer le résultat dans un casque, puis dire : la caméra revient à l'origine, sans rotation, et rien ne l'explique.

## On a
Soit $A$ une matrice dégénérée (singulière), par exemple :
$$A = \begin{pmatrix} 1 & 2 \\ 2 & 4 \end{pmatrix}, \qquad \det(A) = 1\cdot 4 - 2\cdot 2 = 0$$

**Propriété :** $A$ inversible $\iff \det(A) \neq 0$. Ici $\det(A) = 0$, donc $A^{-1}$ **n'existe pas**.

**Programme naïf :**
```python
def inverse(M):
    d = M[0][0]*M[1][1] - M[0][1]*M[1][0]
    if abs(d) < 1e-12:      # singularité détectée...
        return identity(2)  # ...mais renvoyée sans message
    return inverse_classique(M)
```
Sur $A$ : $\det(A) = 0 \Rightarrow$ la fonction renvoie $I_2$ silencieusement.

**Effet dans le casque :** la matrice de vue dégénère (par exemple après un alignement de repères), l'inverse renvoyé est $I$. La caméra se replace à l'origine, sans rotation, et aucun message ne l'explique.

## Ainsi
$$\det(A) = 0 \;\Rightarrow\; A^{-1} \text{ n'existe pas} \;\Rightarrow\; \text{renvoyer } I \text{ est mathématiquement faux}$$

Le programme confond « pas d'inverse » avec « inverse = identité », deux propositions pourtant distinctes : $\nexists A^{-1} \not\Rightarrow A^{-1} = I$.

## Conclusion
Une matrice singulière n'a pas d'inverse ; renvoyer l'identité sans avertissement produit un comportement silencieux et faux : la caméra saute à l'origine sans rotation ni explication. Il faut soit lever une exception, soit renvoyer un statut d'échec — jamais $I$ sans message.

## Observation
Le pire bug n'est pas celui qui plante, mais celui qui donne un résultat plausible et faux. Une identité « propre » est indiscernable d'un calcul correct ; seul un message explicite ou un test de $\det(M) \stackrel{?}{=} 0$ avant inversion permet de distinguer « inversé » de « dégénéré ».
