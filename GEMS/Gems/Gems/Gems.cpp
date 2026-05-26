#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Game.h"
#include "Graphics.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(COLS * CELL_SIZE + PADDING * 2), static_cast<unsigned int>(ROWS * CELL_SIZE + PADDING * 2) }), "GEMS Game");
    window.setFramerateLimit(60);

    Game game;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    game.handleMouseClick(mousePressed->position.x, mousePressed->position.y);
                }
            }
        }

        game.update();
        drawBoard(window, game.getBoard(), game.getSelectedCell());
    }

    return 0;
}
