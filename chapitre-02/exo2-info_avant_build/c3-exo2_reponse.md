## Enoncé

Lancer `Jenga info` et rendre sa sortie, commenter les informations supplémentaires apportées au fichier projet

## Résolution

### Sortie de `Jenga info`

```shell
$Jenga info
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

=========================== Jenga Workspace: Salle2 ============================

Location: Salle2
Entry file: Salle2\Salle2.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name     Kind         Language   Test   External
================================================
Salle2   ConsoleApp   C++        No     Yes


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

### Observations

>Jenga info apporte des informations sur le workspace (Location, Entry, Configuration, TargetOS, TargetArch) que le fichier de projet seul n'apporte pas mais qu'on retrouve dans le fichier du workspace.
>Cette commande indique aussi si les test unitaires ont été activé ou non et si le projet est un bibliothèque statique ou partagée.
>En dernier, elle renseigne sur les toolchains disponibles sur l'appareil ayant éxécuté la commande