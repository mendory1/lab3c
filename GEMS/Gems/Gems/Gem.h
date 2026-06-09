#pragma once
#include <vector>
#include "Config.h"

class Gem {
protected:
    int color;

public:
    Gem(int col) : color(col) {}
    virtual ~Gem() = default;

    int getColor() const { return color; }

    virtual void onDestroy(int board[ROWS][COLS], int myR, int myC) = 0;
};

std::vector<Point> getNeighbors(int startR, int startC);
