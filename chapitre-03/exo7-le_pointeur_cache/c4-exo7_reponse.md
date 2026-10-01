# Chapitre 3 – Exercice 7 : Le pointeur caché

> Dépôt : `ani-4087/chapitre-03/exo7-le_pointeur_cache/` · Fichier : `c4-exo7_reponse.md`

## 1. Énoncé

Nous cachons le curseur et nous le confinons. Nous affichons à chaque image la position `x`, `y` et le `rawDelta`.

Nous bougeons la souris jusqu'à ce qu'elle atteigne le bord. Nous rendons les deux séries et nous disons laquelle continue de bouger, et pourquoi c'est celle-là qu'il faut.

## 2. Étapes de résolution

1. Repartir du projet de l'exercice 1.
2. Activer le masquage et le confinement du curseur .
3. À chaque image, afficher `x`, `y` et `rawDelta` (format CSV : `t_ms,x,y,rawDeltaX,rawDeltaY`) dans un fichier.
4. Déplacer la souris dans une seule direction jusqu'à dépasser largement le bord, puis continuer 5 secondes.
5. Repérer l'image où `x` (ou `y`) cesse de varier, et compter combien d'images `rawDelta` continue d'être non nul après.
6. Expliquer pourquoi le mouvement brut est la bonne source pour une caméra 3D (pas de limite d'écran).

## 0. Environnement de mesure (à remplir une seule fois par session)

| Élément | Valeur |
|---|---|
| Date / heure |30/09/2026 , 18h55 |
| OS + version | Win11 , 22H2|
| CPU / RAM |i7 7th / 16 Go |
| Compilateur |clang-mingw |
| Version de Jenga |2.8.4 |
| Écran : résolution / mise à l'échelle (DPI %) / fréquence | 3840 x 2160 / 282 DPI / 60Hz |
| Mode d'alimentation (secteur / batterie) | secteur |
| Applications lourdes ouvertes en fond ? | non|

## 4. Méthodologie de mesure

**Ce qu'on mesure** : le décalage entre la position (bornée) et le mouvement brut (non borné).

- **Analyse** (script ou tableur) : image de saturation = première image où `x` est égal à sa valeur maximale ; nombre d'images après saturation avec `rawDelta ≠ 0` ; somme des `rawDelta` après saturation (unité : celle du moteur, à préciser).
- **Nombre de lignes** :
- **n = 3 essais**, même direction, même vitesse approximative

.

## 5. Code source

- [`main.cpp`](src/main.cpp)


```cpp
while (running) {
        ++numeroImage;

        nkentseu::NkEvent* event;
        while ((event = stackEvent.PollEvent()) != nullptr) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }

            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                    running = false;
                }
            }

            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_SPACE) {
                    LibererCurseur();
                }
            }

            if (event->Is<nkentseu::NkMouseMoveEvent>()) {
                auto* moveEvent = static_cast<nkentseu::NkMouseMoveEvent*>(event);
                posX = moveEvent->GetX();
                posY = moveEvent->GetY();
            }

            if (event->Is<nkentseu::NkMouseRawEvent>()) {
                auto* rawEvent = static_cast<nkentseu::NkMouseRawEvent*>(event);
                rawDx = rawEvent->GetDeltaX();
                rawDy = rawEvent->GetDeltaY();
            }
        }

        // A chaque image : x, y et rawDelta
        std::cout << "image " << numeroImage
                  << " | x=" << posX << " y=" << posY
                  << " | rawDelta=(" << rawDx << ", " << rawDy << ")"
                  << std::endl;
    }
```



## 7. Résultats

| Essai | Image de saturation | Position figée |Raw Delta à la saturation| Somme après |
|---|---|---|---|---|
| 1 | 907| x=983, y=0|(30,-17) |(1548,565)|
| 2 | 210| x=0, y=0 |(-5,-1) |(346-666)|
| 3 | 775| x=983, y=0 |(29,-12) |(-124,293)|


## 8. Analyse

C'est la serie RawDelta qui continue de bouger et c'est celle là qui faut car la position est bornée par la fenêtre: au bord elle cesse d'enregistrer le mouvement de la main. RawDelta mesure le mouvement du capteur de la souris qui n'a pas de bord(en terme logiciel). Pour un geste continu pour faire tourner une camera, c'est la seul serie adapaté car continu
