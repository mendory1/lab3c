#pragma once
#include "Gem.h"

class RegularGem : public Gem {
public:
    RegularGem(int col) : Gem(col) {}

    void onDestroy(int board[ROWS][COLS], int myR, int myC) override;
};
