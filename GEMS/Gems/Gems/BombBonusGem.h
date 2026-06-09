#pragma once
#include "Gem.h"

class BombBonusGem : public Gem {
public:
    BombBonusGem(int col) : Gem(col) {}

    void onDestroy(int board[ROWS][COLS], int myR, int myC) override;
};
