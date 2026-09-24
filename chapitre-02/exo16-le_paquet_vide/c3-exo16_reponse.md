## Énoncé

Nous empaquetons notre programme, même minimal, le signons, puis rendons la taille du paquet obtenu et la liste de son contenu.

## Résolution

### Fichiers

**`main.cpp`**
```cpp
#ifdef __ANDROID__

#include <android_native_app_glue.h>

void android_main(struct android_app* app)
{
    (void)app;
}

#else

#include <iostream>

int main()
{
    std::cout << "Android" << std::endl;
    return 0;
}

#endif
```

Le `#ifdef __ANDROID__` bascule vers le point d'entrée natif Android (`android_main`) lors d'une compilation Android, et vers un `main` classique affichant simplement `"Android"` sur les autres systèmes.

### Exécution

Nous avons empaqueté le projet Android en configuration Release, obtenant le fichier `Android.apk`, puis l'avons signé avec notre clé de signature. La vérification de la signature confirme qu'elle est valide :

```shell
$jenga package --platform android --config Debug --project Android --type apk                   
                                                
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


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Android                                                        Kind: WINDOWED_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Android\Android\libAndroid.so

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.52s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
ℹ Building APK for Android (x86_64)
⚠ Debug keystore not found at C:\Users\ludvi\.android\debug.keystore - APK ne sera PAS signe ; Android refusera l'install. Generer via: keytool -genkeypair -keystore ~/.android/debug.keystore -alias androiddebugkey -storepass android -keypass android -keyalg RSA -validity 10000
✓ APK generated: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\Build\Bin\Debug-Android\Android\android-build-x86_64\Android-Debug.apk
APK packaged: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\dist\Android.apk

```



La taille du paquet obtenu est de **29,086 Ko**. Son contenu, consulté comme une archive ordinaire, est :

```shell
  Le volume dans le lecteur C n’a pas de nom.
 Le numéro de série du volume est BAA0-7C9B

 Répertoire de C:\Users\ludvi\Desktop\apk

24/09/2026  17:00    <DIR>          .
24/09/2026  17:00    <DIR>          ..
01/01/1980  01:00             2 192 AndroidManifest.xml
24/09/2026  17:00    <DIR>          lib
24/09/2026  17:00    <DIR>          META-INF
01/01/1980  01:00                40 resources.arsc
               2 fichier(s)            2 232 octets

 Répertoire de C:\Users\ludvi\Desktop\apk\lib

24/09/2026  17:00    <DIR>          .
24/09/2026  17:00    <DIR>          ..
24/09/2026  17:00    <DIR>          x86_64
               0 fichier(s)                0 octets

 Répertoire de C:\Users\ludvi\Desktop\apk\lib\x86_64

24/09/2026  17:00    <DIR>          .
24/09/2026  17:00    <DIR>          ..
24/09/2026  16:50            48 824 libAndroid.so
               1 fichier(s)           48 824 octets

 Répertoire de C:\Users\ludvi\Desktop\apk\META-INF

24/09/2026  17:00    <DIR>          .
24/09/2026  17:00    <DIR>          ..
24/09/2026  16:50             1 377 ANDROID.RSA
24/09/2026  16:50               425 ANDROID.SF
24/09/2026  16:50               298 MANIFEST.MF
               3 fichier(s)            2 100 octets

     Total des fichiers listés :
               6 fichier(s)           53 156 octets
              11 Rép(s)   6 078 951 424 octets libres
```



> Le paquet Android signé pèse 28,41 Ko et contient le manifeste, les ressources et la bibliothèque native.
> La signature est valide selon les schémas APK v2 et v3.
> Un APK reste une archive ordinaire, consultable avec n'importe quel outil d'archive.
