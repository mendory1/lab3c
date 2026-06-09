#include "BombBonusGem.h"
#include <algorithm>
#include <random>

void BombBonusGem::onDestroy(int board[ROWS][COLS], int myR, int myC) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<Point> allCells;
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (r != myR || c != myC) {
                allCells.push_back({ r, c });
            }
        }
    }
    std::shuffle(allCells.begin(), allCells.end(), g);

    int toDestroy = std::min(4, (int)allCells.size());
    for (int i = 0; i < toDestroy; ++i) {
        board[allCells[i].r][allCells[i].c] = 0;
    }
}
