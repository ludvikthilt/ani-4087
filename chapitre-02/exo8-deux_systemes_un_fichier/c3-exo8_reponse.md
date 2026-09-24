## Énoncé

Nous écrivons les filtres Windows et Linux avec leurs bibliothèques, faisons vérifier la construction sur l'autre système par un camarade, et indiquons ce que nous n'avons pas pu vérifier si nous n'avons accès qu'à un seul système.

## Résolution
### Fichiers

**`Filtre.jenga`**
```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Filtre - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("Filtre"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])

    
    with filter("system:Windows"):
            links(["user32", "gdi32", "opengl32", "dinput8", "dxguid", "winmm"])

    with filter("system:Linux"):
            links(["pthread", "X11", "Xext", "GL"])
```

Le filtre Windows ajoute les bibliothèques nécessaires pour Windows, le filtre Linux celles nécessaires pour Linux.

**`main.cpp`**
```cpp
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif

int main(){
    #ifdef _WIN32
        std::cout << "OS : Windows" << std::endl;
    #elif defined(__linux__)
        std::cout << "OS : Linux" << std::endl;
    #else
        std::cout << "OS : Inconnu" << std::endl;
    #endif

    return 0;
}
```

`_WIN32` cible Windows et `__linux__` cible Linux ; ces `#ifdef` déterminent quelles parties du code sont compilées, indépendamment des filtres du fichier `.jenga` qui déterminent quelles bibliothèques sont liées.

### Exécution

Nous avons construit et exécuté le projet sous Windows. Les informations importantes de la sortie de construction sont :
```shell
Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Filtre [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Filtre                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Filtre\Filtre.exe
```

Le programme affiche ensuite :
```shell
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Filtre.exe
     D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\Build\Bin\Debug-Windows\Filtre\Filtre.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

OS : Windows

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Nous n'avons pas eu accès à un système Linux, nous avons utiliser wsl2 et nous avons remarquer que le commande `$jenga run --target NomProjet` dirigeait par défaut sur le build windows nous avons donc lancé l'éxécution manuellement.(sur Jenga 2.0.9)

Les informations importantes de la sortie de construction sont :
```shell
Configuration: Debug
Target:        Linux x86_64
Toolchain:     host-gcc

Build Order (1 projects):
  1. Filtre [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Filtre                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓ All files up to date
ℹ Linking...
✓ Built: Build/Bin/Debug-Linux/Filtre/Filtre```
---
```

Les element d'interface cli et le temps d"éxécution ne sont pas affiché car comme nous l'avons dit nous exécutons directement avec `$Build/Bin/Debug-Linux/Filtre/Filtre`, tout de même, le programme affiche ensuite :
```shell
OS : Linux
```

> Les filtres `.jenga` choisissent les bibliothèques liées, pas le code compilé.
> Les `#ifdef` choisissent le code compilé selon le système.

