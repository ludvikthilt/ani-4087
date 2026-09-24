# Exercice 13

## Énoncé

Nous consultons la liste détaillée des toolchains et rendons le tableau complet, en précisant ce qui est présent sur notre machine et ce qui manque.

## Résolution
    exécution de la commande `$jenga info` dan un projet
### Exécution
```shell
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
```
 >Cette liste n'indique pas explicitement ce qui manque : elle affiche uniquement ce qui est disponible. En la comparant à la documentation du projet, d'autres toolchains comme `clang-native` ou `clang-cl` existent mais n'apparaissent pas ici : elles ne sont donc pas détectées ou pas encore installées sur notre machine actuellement.

---


