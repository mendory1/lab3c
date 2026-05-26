#include "Graphics.h"
#include "Config.h"

void drawBoard(sf::RenderWindow& window, const int board[ROWS][COLS], const sf::Vector2i& selectedCell) {
    window.clear(sf::Color(30, 30, 30));

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            sf::RectangleShape shape(sf::Vector2f(static_cast<float>(CELL_SIZE - 4), static_cast<float>(CELL_SIZE - 4)));
            shape.setPosition(sf::Vector2f(static_cast<float>(c * CELL_SIZE + PADDING), static_cast<float>(r * CELL_SIZE + PADDING)));

            if (board[r][c] > 0) {
                shape.setFillColor(Colors[board[r][c]]);

                if (selectedCell.x == c && selectedCell.y == r) {
                    shape.setOutlineThickness(3);
                    shape.setOutlineColor(sf::Color::White);
                }
                else {
                    shape.setOutlineThickness(0);
                }

                window.draw(shape);
            }
        }
    }
    window.display();
}
