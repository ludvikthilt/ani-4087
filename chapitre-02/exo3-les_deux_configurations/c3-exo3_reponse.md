## Enoncé

Construisons un projet en Debug puis en Release et comparons le temps de construction et la taille des éxécutables.

## Résolution

* Debug

```shell

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Salle_Debug [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle_Debug                                                     Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Salle_Debug\Salle_Debug.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.76s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.76s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
* Release

```shell

Configuration: Release
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Salle_Debug [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle_Debug                                                     Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Salle_Debug\Salle_Debug.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.77s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.77s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```

>NB : Lors de le création d'un projet directement dans la création d'un workspace , avec la configuration release, les sorties du build marque Debug (Jenga 2.8.0)




### Comparaison

| |Taille de l'éxécutable(o)|Temps de construction(ms)
|---|---|---|
Debug| 52224|763,78
Release| 52224|772,19

> Les temps d'éxécutions et les tailles des fichiers exécutables sont similaire en release et en debug, les mesures sont faite avec des commandes dédiées
