## Énoncé

Nous lisons en entier le fichier de projet de la démonstration XR du moteur, commentaires compris, et rendons compte de ce qu'il construit, de ses dépendances, de ce qui change selon le système, ainsi que des trois pièges qu'il documente et de ce qui se passerait sans chacun.

## Résolution

Nous avons repéré l'exemple `27_nk_window`, consacré au système de fenêtrage multiplateforme `NKWindow`, puis copié son fichier de projet dans notre dossier de travail pour le lire intégralement.

### Ce que construit le projet

Le projet construit une bibliothèque statique `NKWindow`, qui gère les fenêtres et les événements de manière multiplateforme, ainsi que trois applications de démonstration (`Sandbox`, `SandboxCamera`, `SandboxCameraFull`) qui l'utilisent. Il se construit en Debug ou en Release, en C++17.

### Dépendances

Le projet dépend des répertoires `src` et `../Externals`, et les démonstrations dépendent de `NKWindow` lui-même. Les bibliothèques liées varient ensuite selon le système : `user32`, `gdi32`, `opengl32`, `dwmapi`, `shell32`, `xinput` sous Windows ; `pthread`, `X11` sous Linux ; `android`, `log`, `EGL`, `GLESv3`, `camera2ndk`, `mediandk` sous Android.

### Ce qui change d'un système à l'autre

Le fichier utilise des filtres par système pour cibler sept plateformes (Windows, Linux, macOS, Android, iOS, Web, HarmonyOS), chacune avec son propre backend : Win32 sous Windows, XLib/X11 sous Linux (avec une variante NOOP en mode headless), Cocoa sous macOS, NDK/NativeActivity/EGL sous Android, UIKit sous iOS, Emscripten/WebAssembly sur le Web, et un backend Noop temporaire sous HarmonyOS.

### Les trois pièges documentés

- **Le mode Linux headless** : un filtre combinant `system:Linux` et l'option `headless` bascule sur un backend NOOP. Sans lui, le projet tenterait d'utiliser X11 alors qu'aucun affichage n'est disponible, ce qui casserait son fonctionnement en CI ou sous WSL.
- **`ASYNCIFY` pour le Web** : cette option Emscripten est nécessaire aux boucles synchrones de type desktop. Sans elle, ces boucles risqueraient de ne pas fonctionner correctement une fois compilées pour le Web.
- **Le repli HarmonyOS** : en l'absence de backend HarmonyOS réel, le projet inclut des fichiers Noop comme solution temporaire. Sans ce repli, il manquerait les fichiers d'implémentation nécessaires et la cible ne compilerait pas.



> Le fichier de projet définit ce qui est construit, les dépendances et les réglages propres à chaque système.
> Trois pièges y sont documentés : le mode headless Linux, l'option ASYNCIFY sur le Web et le repli HarmonyOS.
> Chacun évite un échec ou un comportement incorrect propre à sa plateforme.
