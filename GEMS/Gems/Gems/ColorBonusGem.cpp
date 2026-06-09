#include "ColorBonusGem.h"
#include <cmath>
#include <algorithm>
#include <random>

void ColorBonusGem::onDestroy(int board[ROWS][COLS], int myR, int myC) {
    std::random_device rd;
    std::mt19937 g(rd());

    auto area = getNeighbors(myR, myC);
    if (area.empty()) return;
    std::shuffle(area.begin(), area.end(), g);

    int changedCount = 0;
    for (size_t i = 0; changedCount < 2 && i < area.size(); ++i) {
        Point p = area[i];
        if (p.r == myR && p.c == myC) continue;

        if (std::abs(p.r - myR) + std::abs(p.c - myC) > 1) {
            board[p.r][p.c] = color;
            changedCount++;
        }
    }
}
