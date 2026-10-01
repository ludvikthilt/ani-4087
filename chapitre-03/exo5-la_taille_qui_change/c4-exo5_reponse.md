# Chapitre 3 – Exercice 5 : La taille qui change

> Dépôt : `ani-4087/chapitre-03/exo5-la_taille_qui_change/` · Fichier : `c4-exo5_reponse.md`

## 1. Énoncé

Nous écoutons `NkWindowResizeEvent` et nous affichons la nouvelle taille dans la console à chaque changement.

Nous redimensionnons lentement, puis d'un coup. Nous rendons les deux séries de nombres, et nous disons ce que nous en concluons sur le nombre d'événements reçus.

## 2. Étapes de résolution

1. Ajouter un compteur `nbEvenements` et un rappel sur `NkWindowResizeEvent` qui l'incrémente et affiche `#n : largeur x hauteur` avec un horodatage.
2. Rediriger la sortie console vers un fichier de log pour chaque série (`> resize_lent.log`).
3. Série 1 – **lente** : glisser un bord de la fenêtre sur une distance fixe pendant une durée fixe (10 s).
4. Série 2 – **brusque** : même distance couverte en un seul geste rapide (ou maximisation, à préciser).
5. Compter les lignes des logs et comparer avec le compteur affiché en fin de programme.
6. Conclure : le nombre d'événements dépend-il de la distance, de la vitesse, ou des deux ?

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

**Ce qu'on mesure** : nombre d'événements de redimensionnement et taille finale, pour deux vitesses.

- **Conditions identiques** : même taille de départ (1280×720), même taille d'arrivée visée, même bord saisi.
- **Durée du geste** : via les horodatages du log (dernier − premier).
- **Comptage** : le compteur du programme **et** le nombre de lignes du fichier de log (la partie des redimensionnements), qui doivent être égaux :
  - PowerShell : `(Get-Content resize_lent.log | Measure-Object -Line).Lines`
- **Taille des logs** (indicateur secondaire) : `(Get-Item resize_lent.log).Length` .
- **n = 5 répétitions par série.** On rapporte, pour chaque série : nombre d'événements (moy ± σ), événements par seconde, événements par 100 pixels parcourus.
- Aucune autre interaction avec la fenêtre pendant un essai.

**Traitement statistique** (voir [`../../mesures/stats.py`](../../mesures/stats.py)) :
`python ../../mesures/stats.py v1 v2 v3 ...` renvoie n, moyenne, médiane, écart-type (échantillon), min, max.
On rapporte toujours **moyenne ± écart-type (n = …)** et on signale toute valeur aberrante au lieu de la supprimer en silence.

## 5. Code source

- [`main.cpp`](src/main.cpp)
- [`resize_lent.log`](src/resize_lent.log)
- [`resize_brusque.log`](src/resize_brusque.log)

```cpp
int nkmain(const nkentseu::NkEntryState &state){
    nkentseu::NkWindowConfig config;
    config.title = "la fenetre nue";
    config.width = 1000;
    config.height = 720;

    
    nkentseu::NkWindow fenetre(config);

    if(!fenetre.IsValid()){
        return 1;
    }
    //int count = 0;
    bool running= true ;
    auto& stackEvent = nkentseu::NkEvents();

    // compteur d'evenements de redirection
    int nbEvenements = 0;
    
    while (running){
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr){
            //std::cout<<"evenement reçu"<<std::endl;
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }
            if(event->Is<nkentseu::NkKeyPressEvent>()){
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                   running = false;
                }
            }

            if(event->Is<nkentseu::NkWindowResizeEvent>()){
                auto* resizeEvent = static_cast<nkentseu::NkWindowResizeEvent*>(event);
                SurRedimensionnement(nbEvenements, resizeEvent->GetWidth(), resizeEvent->GetHeight());
                count++;

                std::cout <<"resize"<<std::endl;
        
            }
                
        }
        
    }
std::cout<<"\nNombre d'evenements : "<<nbEvenements<<std::endl;
 return 0;
   
}
```



## 6. Résultats

| Essai | Lent : nb événements | Brusque : nb événements |
|---|---|---|
| 1 | 203 | 21|
| 2 | 201| 24|
| 3 | 201| 21|
| 4 | 183| 25|
| 5 | 192| 26|
| **Moy ± σ** |( 196.0000 ± 8.4261)| (23.4000 ±  2.3022) |

## 8. Analyse

Le nombre d'évènements reçu est grandement affecté par le temps mis pour redimmensionner la fenetre. L'on pourrait croire que l'avancement sur un pixel ou sur une autre unité de mesure represente un evenement mais ce n'est pas le cas, les evenements sont interprétés differemment.
