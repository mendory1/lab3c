#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Bonus.h"
#include "Input.h"

class Game {
private:
    int board[ROWS][COLS];

    Input input;
    Bonus bonus;

    void fillEmptyCells();
    bool findMatches(bool markedToDestroy[ROWS][COLS]);
    void floodFill(int r, int c, int color, bool visited[ROWS][COLS], std::vector<Point>& component);
    void processDestruction();
    void dropGems();

public:
    Game();
    void initBoard();
    void handleMouseClick(int mouseX, int mouseY);
    void update();

    auto getBoard() -> const int(*)[COLS] { return board; }
    sf::Vector2i getSelectedCell() { return input.getSelectedCell();
    }
};
