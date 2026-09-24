## Énoncé

Nous classons les vingt-trois dépendances de la démonstration en trois groupes selon notre niveau de certitude sur leur rôle, et rédigeons une phrase par module pour celles que nous ne connaissons pas.

## Résolution

La liste vient du fichier `Applications/NKXRDemo/NKXRDemo.jenga` :

```
nkentseudependson(
    ["NKXR", "NKRenderer", "NKRHI", "NKSL", "NKGLSlang", "NKSPIRVCross",
     "NKSerialization", "NKReflection", "NKFileSystem", "NKFont", "NKImage", "NKGlad",
     "NKEvent", "NKWindow", "NKMath", "NKTime", "NKLogger", "NKStream",
     "NKContainers", "NKMemory", "NKCore", "NKPlatform", "NKThreading"]
)
```

### 1. Rôle facile à deviner

- **NKXR** : réalité virtuelle / XR
- **NKRenderer** : rendu graphique
- **NKSerialization** : sérialisation des données
- **NKReflection** : réflexion
- **NKFileSystem** : système de fichiers
- **NKFont** : gestion des polices
- **NKImage** : gestion des images
- **NKEvent** : gestion des événements
- **NKWindow** : gestion des fenêtres
- **NKMath** : mathématiques
- **NKTime** : gestion du temps
- **NKLogger** : gestion des logs
- **NKStream** : gestion des flux
- **NKContainers** : conteneurs de données
- **NKMemory** : gestion de la mémoire
- **NKCore** : fonctionnalités principales / de base
- **NKPlatform** : gestion de la plateforme
- **NKThreading** : gestion des threads

### 2. Idée sans certitude

- **NKRHI** : probablement une interface avec le matériel ou le système de rendu graphique.
- **NKSL** : probablement lié aux shaders ou à leur gestion.
- **NKGlad** : probablement lié à OpenGL et au chargement de ses fonctions.

### 3. Rôle inconnu au départ

Après avoir regardé les en-têtes principaux :

- **NKGLSlang** : fournit les éléments nécessaires pour travailler avec le langage de shaders GLSL.
- **NKSPIRVCross** : permet de travailler avec SPIR-V et de convertir entre formats ou langages de shaders.

Une grande partie des modules se devine facilement par leur nom. `NKGLSlang` et `NKSPIRVCross` restent les moins intuitifs. Il a fallu consulter leur code pour comprendre leur rôle exact.
