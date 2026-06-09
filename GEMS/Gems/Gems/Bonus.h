#pragma once
#include <vector>
#include "Config.h"

class Bonus {
private:
    std::vector<Point> getValidNeighbors(int startR, int startC);

public:
    void triggerInstantBonus(int board[ROWS][COLS], int targetR, int targetC, int bonusType, int originalColor);
};
