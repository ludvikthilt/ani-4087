## Enoncé

Reprendre le tableau des cinq étapes du chapitre. Pour chacune, chercher une source qui donne une valeur mesurée. Rendre le tableau avec les sources. Dire quand une valeur est introuvable plutôt que d'inventer.

## Sachant que

Les cinq étapes du livre sont : capteurs, transmission, application, compositeur, affichage. Une valeur mesurée doit venir d'une source identifiable (article, documentation constructeur), pas d'une estimation personnelle.

## On a

| Étape | Valeur du livre | Valeur trouvée | Source |
|---|---|---|---|
| Capteurs mesurent | 1–2 ms | ~1 ms (IMU à 1000 Hz, donc échantillon vieux d'1 ms au pire) | Wagner, *Motion-to-Photon Latency in Mobile AR and VR*, Medium/DAQRI, 2018 |
| Transmission | 1–3 ms | **Introuvable** isolément | Brennan et al., *Behavior Research Methods*, 2022 décrit l'étape mais ne la chiffre jamais séparément du reste du pipeline |
| Application décide et dessine | 5–11 ms | **Introuvable** comme valeur isolée fiable | Carmack, *Latency Mitigation Strategies*, 2013, discute le rendu comme premier poste de latence mais sans chiffre isolé généralisable (dépend de la scène) |
| Compositeur assemble | 1–2 ms | **Introuvable** | La doc Meta sur l'Asynchronous TimeWarp explique la technique mais ne publie pas de durée en ms |
| Écran affiche | 2–5 ms | ~2 ms sur une image de 7 ms (persistance basse) | Mantiuk et al., *elaTCSF*, arXiv 2503.16759, 2025 |

## Ainsi

Trois étapes sur cinq (transmission, rendu applicatif, composition) n'ont pas de valeur isolée publique fiable : les mesures publiées portent presque toujours sur la latence totale mouvement-vers-photon, pas sur chaque maillon séparément. 
