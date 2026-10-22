# Chapitre 6 — Exercice 1 : Le pointeur capturé

## Fichiers

- [pointeur.cpp](pointeur.cpp)
- [essais.txt](essais.txt)
- [exo1.jenga](exo1.jenga)
- [Capture et clip actifs](capture-active.png)
- [Capture relâchée](capture-relachee.png)
- [Salle de départ et touches de test](../main.cpp)

## Réalisation et comportement

Le programme crée une fenêtre et utilise les appels séparés de NkWindow : `CaptureMouse` capture les événements, `ClipMouseToClient` confine le curseur à la zone cliente, et `ShowMouse` règle sa visibilité. Au démarrage, capture et clip sont activés; la barre Espace alterne entre l’état capturé/confiné et l’état relâché. Échap et la fermeture de la fenêtre terminent la boucle. Le nettoyage désactive le clip, libère la capture et réaffiche le pointeur avant de quitter.

Les captures montrent les deux états dans le titre de fenêtre : [capture et clip actifs](capture-active.png), puis [capture relâchée](capture-relachee.png). Elles documentent les états de l’application, mais ne sont pas une mesure du déplacement physique du pointeur.

| Essai | Résultat établi par les appels du programme et le contrat de NkWindow |
|---|---|
| Avec CaptureMouse seul | Les événements souris restent dirigés vers la fenêtre, mais le curseur n’est pas confiné et peut sortir de sa zone. |
| Ce qui le retient | `ClipMouseToClient(true)` applique le confinement au rectangle client ; la capture seule ne le fait pas. |
| Deux appuis de suite | Le premier appui libère capture/clip et réaffiche le curseur ; le second restaure capture/clip et le masque. L’état revient à son état initial. |
| Fermeture sans relâcher | Le chemin de fermeture exécute le nettoyage explicite avant la destruction de la fenêtre. Le clip est désactivé, la capture est libérée et le pointeur réaffiché. |

Ces résultats décrivent le chemin de code et les garanties documentées de l’API ; le déplacement manuel du curseur et la fermeture effective d’une fenêtre n’ont pas été observés dans cette session. Le journal de cette distinction figure dans [essais.txt](essais.txt).

## Conclusion

La capture d’événements et le confinement sont deux opérations différentes : seule la seconde retient physiquement le curseur dans la fenêtre. La libération doit être explicite, notamment pour ne pas laisser le clip actif après fermeture. Sous Windows, `ShowMouse` utilise un compteur système ; le code équilibre donc les changements de visibilité lors de chaque transition et du nettoyage.
