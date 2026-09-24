## Enonce

Enonçons un petit entête à vous qui déclare une classe complète si un define est posé et une coquille vide sinon. Compilons avec et sans le define. Rendons les deux messages d'erreurs.

## Résolution

- Fichiers

`machine.hpp`

```cpp
    #define AVEC_DEFINE  //commenter la ligne pour annuler le define

    #ifdef AVEC_DEFINE
    class Machine {
        public : 
            Machine(int v) : val(v) {}
            int val;
    };
    #else
    class Machine {};
    #endif
```

`main.cpp`

```cpp
    #include "machine.hpp"

    int main() {
        Machine m(15);
    }

```

- Messages
  - Message 1 (aucune erreur)

```shell

    Build Order (1 projects):
    1. Salle_Define_Class [CONSOLE_APP]


    ╔══════════════════════════════════════════════════════════════════════════════════════════════╗
    ║  Project: Salle_Define_Class                                              Kind: CONSOLE_APP  ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════╝

    ℹ Found 1 source file(s)
    ✓   [1/1] Compiled: main.cpp
    ℹ Linking...
    ✓ Built: Build\Bin\Debug-Windows\Salle_Define_Class\Salle_Define_Class.exe

    ┌──────────────────────────────────────────────────────────────────────────────────────────────┐
    │  ✓ Build Successful                                                             Time: 0.38s  │
    └──────────────────────────────────────────────────────────────────────────────────────────────┘

    ════════════════════════════════════════════════════════════════════════════════
                                    BUILD COMPLETED
    ════════════════════════════════════════════════════════════════════════════════
    Projects Built:  1/1
    Time:           0.38s
    Status:         ✓ SUCCESS
    ════════════════════════════════════════════════════════════════════════════════
```


  - Message 2(erreur)
```shell
1. Salle_Define_Class [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Salle_Define_Class                                              Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Define_Class\Salle_Define_Class\src\main.cpp:4:13: error:   ║
║ no matching constructor for initialization of 'Machine'                                      ║
║     4 |     Machine m(15);                                                                   ║
║       |             ^ ~~                                                                     ║
║ D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Define_Class\Salle_Define_Class\src/machine.hpp:10:7: note: ║
║ candidate constructor (the implicit copy constructor) not viable: no known conversion from   ║
║ 'int' to 'const Machine' for 1st argument                                                    ║
║    10 | class Machine {};                                                                    ║
║       |       ^~~~~~~                                                                        ║
║ D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Define_Class\Salle_Define_Class\src/machine.hpp:10:7: note: ║
║ candidate constructor (the implicit move constructor) not viable: no known conversion from   ║
║ 'int' to 'Machine' for 1st argument                                                          ║
║    10 | class Machine {};                                                                    ║
║       |       ^~~~~~~                                                                        ║
║ D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Define_Class\Salle_Define_Class\src/machine.hpp:10:7: note: ║
║ candidate constructor (the implicit default constructor) not viable: requires 0 arguments,   ║
║ but 1 was provided                                                                           ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\COURS_ENSPY\L4\AR_VR_XR\Salle_Define_Class\Salle_Define_Class\src\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.13s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD FAILED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.13s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
✗ Salle_Define_Class

```

>Nous aurions pu diagnostiquer le deuxième message, car je passe un paramètre lors de la déclaration de l'objet  pourtant sans le define il n'a pas de constructeur
