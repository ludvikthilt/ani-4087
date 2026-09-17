## Énoncé

Écrire un programme sur écran qui suit la souris avec un retard réglable, de 0 à 200 ms. Le faire essayer à cinq personnes et noter le seuil à partir duquel chacune sent quelque chose. Comparer au budget de vingt millisecondes.

## Principe du programme

Un curseur suit la position de la souris, mais affiche une position mémorisée N millisecondes plus tôt (file d'attente de positions horodatées, on affiche la plus ancienne encore valide). Les flèches haut/bas règlent N de 0 à 200 ms en direct.

## Code (C++17, SFML)

## Code (C++17, SFML 3)

```cpp
#include <SFML/Graphics.hpp>
#include <chrono>
#include <deque>
#include <optional>

struct Sample {
    std::chrono::steady_clock::time_point t;
    sf::Vector2i pos;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Retard reglable");
    window.setFramerateLimit(120);

    std::deque<Sample> history;
    int delayMs = 0; // 0 a 200 ms, pas de 10

    sf::CircleShape cursor(8.f);
    cursor.setFillColor(sf::Color::Red);
    cursor.setOrigin({8.f, 8.f});

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) // a adapter selon le systeme
        return 1;
    sf::Text label(font, "", 20);
    label.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Up && delayMs < 200) delayMs += 10;
                if (key->code == sf::Keyboard::Key::Down && delayMs > 0) delayMs -= 10;
            }
        }

        // enregistre la position actuelle, horodatee
        auto now = std::chrono::steady_clock::now();
        history.push_back({now, sf::Mouse::getPosition(window)});

        // jette les echantillons trop vieux (garde une marge)
        while (history.size() > 1 &&
               std::chrono::duration_cast<std::chrono::milliseconds>(now - history.front().t).count() > 400)
            history.pop_front();

        // cherche la position la plus ancienne encore valide pour le retard demande
        sf::Vector2i shown = history.front().pos;
        for (const auto& s : history) {
            auto age = std::chrono::duration_cast<std::chrono::milliseconds>(now - s.t).count();
            if (age >= delayMs) shown = s.pos;
            else break;
        }

        cursor.setPosition({static_cast<float>(shown.x), static_cast<float>(shown.y)});
        label.setString("retard : " + std::to_string(delayMs) + " ms  (haut/bas pour regler)");

        window.clear(sf::Color::Black);
        window.draw(cursor);
        window.draw(label);
        window.display();
    }
    return 0;
}
```


## Données reccueillies

| Personne | Seuil ressenti (ms) |
|---|---|
| P1 | 100 |
| P2 | 110 |
| P3 | 90 |
| P4 | 110 |
| P5 | 100 |


