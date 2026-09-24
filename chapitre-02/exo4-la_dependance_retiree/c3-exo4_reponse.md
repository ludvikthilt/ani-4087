## Enonce

Ajoutons a notre projet un module qui depend lui-meme d'un autre, puis retirons le second de notre liste. Rendons le message d'erreur et determinons a quel type d'erreur il s'agit

## Résolution

- Fichiers

`depend_module.h`

```cpp
    #pragma once
    void hello();

```

`depend_module.cpp`

```cpp
    #include "depend_module.h"
    #include "missing_module.h"

    void hello() {
        greet();
    }
```

`main.cpp`

```cpp
    #include "depend_module.h"

    int main() {
    hello();
        return 0;
    }

```

- Message d'erreur

```shell

Build Order (1 projects):
  1. Salle_Missing_Module [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle_Missing_Module                                            Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 2 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: depend_module.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Missing_Module\Salle_Missing_Module\src\depend_module.cpp:2 ║
║ :10: fatal error: 'missing_module.h' file not found                                          ║
║     2 | #include "missing_module.h"                                                          ║
║       |          ^~~~~~~~~~~~~~~~~~                                                          ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Missing_Module\Salle_Missing_Module\src\depend_module.cpp
✓   [2/2] Compiled: main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.14s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.14s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ Salle_Missing_Module
```

>L'erreur appatient au type d'erreur *preprocesseur* car , la directive `#include` est traitée avant toute compilation, et c'est le processeur ui echou donc à trouver le fichier. A savoir qu'avec  `import` de (C++ 20, C++23) il s'agit d'une erreur de *compilation* car le compilatuer cherche un fichier module déjà précompilé.