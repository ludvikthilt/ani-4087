## Énoncé

Nous ajoutons à notre fichier de projet le filtre Android avec ses bibliothèques et définitions, constatons que l'affichage des informations du projet ne change pas selon que le filtre s'applique ou non, puis vérifions autrement qu'il s'active bien pour Android.

## Résolution

### Fichiers

**`Salle.jenga`**
```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Salle - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("Salle"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])
    
    with filter("system:Android"):
            usetoolchain("android-ndk")
            defines(["ANDROID"])
            links(["EGL", "GLESv3", "android", "log"])

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

Le filtre Android ajouté utilise la toolchain `android-ndk`, ajoute la définition `ANDROID` et lie les bibliothèques `EGL`, `GLESv3`, `android` et `log`.

### Exécution

En consultant les informations générales du projet, la sortie obtenue est strictement identique que le filtre Android soit présent ou non : cet affichage ne permet donc pas de vérifier si un filtre par système est actif.

```shell
Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Salle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Salle\Salle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.96s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.96s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```

Pour vérifier réellement l'activation du filtre, nous avons lancé une construction ciblant explicitement la plateforme Android ARM64. Cette fois, la toolchain `android-ndk` a bien été utilisée et l'exécutable a été généré dans `Build\Bin\Debug-Android\Salle\Salle`, confirmant que le filtre s'applique correctement pour cette plateforme.

```shell
Loading workspace...

Configuration: Debug
Target:        Android arm64
Toolchain:     android-ndk

Build Order (1 projects):
  1. Salle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Android\Salle\Salle

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.33s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.33s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

✓ Executable generated: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\Build\Bin\Debug-Android\Salle\Salle
```
---

> Résumé : L'affichage général des informations du projet ne révèle pas si un filtre par système est actif.
> Seule une construction ciblant explicitement la plateforme concernée le confirme.
> Le filtre Android a bien produit un exécutable pour cette cible.
