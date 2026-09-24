## Énoncé

Nous ajoutons à `files` un motif qui ne correspond à aucun fichier, et à `includedirs` un dossier qui n'existe pas, puis nous comparons ce que révèle l'affichage des informations du projet et ce que révèle sa construction.

## Résolution

### Fichiers

**`CheminInexistant.jenga`**
```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# CheminInexistant - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("CheminInexistant"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/Thilt.cpp"])
    includedirs(["include", "THILT"])

```

Le fichier `src/AIA.cpp` référencé dans `files` n'existe pas, et le dossier `AIA4` référencé dans `includedirs` n'existe pas non plus.

### Exécution

L'affichage des informations générales du projet ne signale pas clairement que le fichier ou le dossier ajouté n'existe pas ; il donne surtout une vue d'ensemble de la configuration.
```shell
========================= Jenga Workspace: Chapitre-02 =========================

Location: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02
Entry file: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\Chapitre-02.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Linux, macOS
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name               Kind         Language   Test   External
==========================================================
Filtre             ConsoleApp   C++        No     Yes
Salle              ConsoleApp   C++        No     Yes
DeuxSystemes       ConsoleApp   C++        No     Yes
CheminInexistant   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name                 Family        Target OS   Arch     Env    
===============================================================
host-clang           clang         Windows     x86_64   mingw
host-gcc             gcc           Windows     x86_64   mingw
clang-mingw          clang         Windows     x86_64   mingw
mingw                gcc           Windows     x86_64   mingw
clang-cross-linux    clang         Linux       x86_64   gnu
android-ndk          android-ndk   Android     arm64    android
emscripten           emscripten    Web         wasm32
zig-linux-x86_64     clang         Linux       x86_64   gnu
zig-linux-x64        clang         Linux       x86_64   gnu
zig-windows-x86_64   clang         Windows     x86_64   mingw
zig-windows-x64      clang         Windows     x86_64   mingw
zig-macos-x86_64     clang         macOS       x86_64   gnu
zig-macos-arm64      clang         macOS       arm64    gnu
zig-ios-arm64        clang         iOS         arm64
zig-tvos-arm64       clang         tvOS        arm64
zig-watchos-arm64    clang         watchOS     arm64
zig-android-arm64    clang         Android     arm64    android
zig-web-wasm32       clang         Web         wasm32


Daemon
------------------------------------------------------------
Status: Not running
```

La construction du projet, elle, vérifie réellement la présence des fichiers nécessaires et fait donc apparaître le problème beaucoup plus clairement.

Entre les deux, la construction nous aurait fait gagner plus de temps, car elle détecte directement le chemin invalide, là où l'affichage des informations ne le fait pas.

```shell
Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. CheminInexistant [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: CheminInexistant                                                Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

No source files found for project CheminInexistant

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.02s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```

---

> Un chemin incorrect n'est pas toujours visible en consultant les informations du projet.
> Pour vérifier rapidement la validité des fichiers et dossiers, lancer la construction est plus fiable.
