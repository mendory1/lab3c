#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"

class Game {
private:
    int board[ROWS][COLS];
    sf::Vector2i selectedCell;
    bool isSelected;

    void fillEmptyCells();
    bool findMatches(bool markedToDestroy[ROWS][COLS]);
    void floodFill(int r, int c, int color, bool visited[ROWS][COLS], std::vector<Point>& component);
    void processDestruction();
    void dropGems();

    void triggerInstantBonus(int targetR, int targetC, int bonusType, int originalColor);
    std::vector<Point> getValidNeighborsInRadius3(int startR, int startC);

public:
    Game();
    void initBoard();
    void handleMouseClick(int mouseX, int mouseY);
    void update();

    auto getBoard() -> const int(*)[COLS] { return board; }
    sf::Vector2i getSelectedCell() { return isSelected ? selectedCell : sf::Vector2i(-1, -1); }
};
