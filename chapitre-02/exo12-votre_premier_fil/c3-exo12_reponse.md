## Énoncé

Nous préparons notre fichier de projet pour tout le livre en ajoutant, en commentaire, une ligne par chapitre à venir décrivant ce qu'il faudra y ajouter, lignes que nous décocherons une à une par la suite.

## Résolution

### Fichiers

**`salle.jenga`**
```python
# Projects actuels
    with project("Salle"):
        consoleapp()
        language("C++")
        location("Salle")
        files(["src/**.cpp", "include/**.hpp"])

    with project("27_nk_window"):
        consoleapp()
        language("C++")
        location("Salle")
        files(["src/**.cpp", "include/**.hpp"])

    # Sprint 3 : NKWindow et NKEvent :
    # gestion de la fenêtre et des événements.

    # Sprint 4 : NKRHI et NKRenderer :
    # gestion du rendu et du backend graphique.

    # Sprint 5 : Images, modèles, textes, sons :
    # gestion des ressources multimédias.

    # Sprint 6 : La tête, l'orientation et les deux yeux :
    # gestion de la tête, de l'orientation et de la stéréoscopie.

    # Sprint 7 : La cadence et la prédiction :
    # gestion de la cadence d'affichage et de la prédiction.

    # Sprint 8 : Les chaînes d'échange :
    # ajouter les mécanismes de communication et d'échange entre les éléments.

    # Sprint 9 : Les actions :
    # gestion des actions et des interactions.

    # Sprint 10 : La composition et les couches :
    # composition des éléments et la gestion des couches.

    # Sprint 11 : Lire le vrai backend, et la même application sur deux backends :
    # ajouter le support et la sélection des différents backends.

    # Sprint 12 : Rendre deux fois :
    # possibilité d'effectuer deux rendus.

    # Sprint 13 : La porte s'ouvre :
    # ajouter les éléments nécessaires à l'ouverture et à la gestion de la porte.

    # Sprint 14 : Des panneaux qu'on lit, et le son qui place les choses :
    # ajouter les panneaux d'information et la gestion du son.

    # Sprint 15 : Quelqu'un d'autre entre :
    # gestion d'un second utilisateur ou personnage.

    # Sprint 16 : Bâtir et livrer :
    # ajouter les éléments nécessaires à la construction et à la livraison du projet.

    # Sprint 17 : Approfondissement :
    # ajouter les fonctionnalités d'approfondissement demandées dans le sprint.
```

Chaque sprint à venir est représenté par une ligne commentée décrivant ce qu'il faudra ajouter au projet. Ces lignes resteront commentées et seront décochées une à une au fil de l'avancement dans le livre, ce qui permet de préparer le projet sans introduire de fonctionnalités pas encore étudiées.

---

> Chaque sprint futur est déjà noté en commentaire dans le fichier de projet.
> Les lignes seront décochées une à une au fur et à mesure de l'avancement.
> Le projet reste ainsi fonctionnel sans anticiper de fonctionnalités non encore vues.
