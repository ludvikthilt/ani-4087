# Exercice 17

## Énoncé

Nous installons notre paquet sur un appareil et le lançons, en rendant une capture d'écran de l'appareil, ou le message exact en cas d'échec.

## Résolution

### Fichiers

**`Android.jenga`** (extrait pertinent)
```python
with project("MaSalle"):
    windowedapp()
    language("C++")
    location("MaSalle")
    files(["src/**.cpp", "include/**.hpp"])

    with filter("system:Android"):
        usetoolchain("android-ndk")
        defines(["ANDROID"])
        links(["EGL", "GLESv3", "android", "log"])

    androidapplicationid("com.monsalle.app")
    androidminsdk(24)
    androidtargetsdk(34)
    androidcompilesdk(34)
    androidabis(["arm64-v8a"])
    androidnativeactivity(True)
    androidversioncode(1)
    androidversionname("1.0")
```

La ligne `androidabis(["arm64-v8a"])` fixe l'architecture Android ciblée par la construction.

### Exécution

#### obtention de l'apk

```shell
ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Android\Android\libAndroid.so

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.46s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
ℹ Building APK for Android (x86_64)
⚠ Debug keystore not found at C:\Users\ludvi\.android\debug.keystore - APK ne sera PAS signe ; Android refusera l'install. Generer via: keytool -genkeypair -keystore ~/.android/debug.keystore -alias androiddebugkey -storepass android -keypass android -keyalg RSA -validity 10000
✓ APK generated: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\Build\Bin\Debug-Android\Android\android-build-x86_64\Android-Debug.apk
APK packaged: D:\COURS_ENSPY\L4\AR_VR_XR\Chapitre-02\dist\Android.apk
```

Notre téléphone Android, connecté et détecté correctement, a refusé l'installation du paquet avec le message exact suivant :

```text
Performing Incremental Install
Performing Streamed Install
adb.exe: failed to install .\dist\MaSalle.apk: Failure [INSTALL_FAILED_NO_MATCHING_ABIS: INSTALL_FAILED_NO_MATCHING_ABIS: Failed to extract native libraries, res=-113]
```

L'échec vient d'une incompatibilité d'architecture : l'APK contient la bibliothèque `lib/x86_64/Android.so`, alors que notre fichier de projet cible l'architecture `arm64-v8a`.

---

> L'installation a échoué faute de bibliothèque native compatible avec l'appareil.
> L'APK visait x86_64 alors que le fichier de projet ciblait arm64-v8a.
> Le message d'erreur exact identifie directement la cause : INSTALL_FAILED_NO_MATCHING_ABIS.
