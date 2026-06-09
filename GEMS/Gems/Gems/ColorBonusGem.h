#pragma once
#include "Gem.h"

class ColorBonusGem : public Gem {
public:
    ColorBonusGem(int col) : Gem(col) {}

    void onDestroy(int board[ROWS][COLS], int myR, int myC) override;
};
