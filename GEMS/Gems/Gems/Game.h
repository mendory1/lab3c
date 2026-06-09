#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Gem.h"
#include "Input.h"

class Game {
private:
    std::unique_ptr<Gem> board[ROWS][COLS];
    int intBoard[ROWS][COLS];

    Input input;

    void fillEmptyCells();
    bool findMatches(bool markedToDestroy[ROWS][COLS]);
    void floodFill(int r, int c, int color, bool visited[ROWS][COLS], std::vector<Point>& component);
    void processDestruction();
    void dropGems();
    void syncIntBoard();

public:
    Game();
    void initBoard();
    void handleMouseClick(int mouseX, int mouseY);
    void update();

    auto getBoard() -> const int(*)[COLS] { return intBoard; }
    sf::Vector2i getSelectedCell() { return input.getSelectedCell();
    }
};
