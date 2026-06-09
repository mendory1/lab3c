#include "Bonus.h"
#include <cmath>
#include <algorithm>
#include <random>

std::vector<Point> Bonus::getValidNeighbors(int startR, int startC) {
    std::vector<Point> targets;
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (std::abs(r - startR) <= 3 && std::abs(c - startC) <= 3) {
                targets.push_back({ r, c });
            }
        }
    }
    return targets;
}

void Bonus::triggerInstantBonus(int board[ROWS][COLS], int targetR, int targetC, int bonusType, int originalColor) {
    std::random_device rd;
    std::mt19937 g(rd());

    if (bonusType == 1) {
        board[targetR][targetC] = originalColor;
        auto area = getValidNeighbors(targetR, targetC);
        std::shuffle(area.begin(), area.end(), g);

        int changedCount = 0;
        for (size_t i = 0; changedCount < 2 && i < area.size(); ++i) {
            Point p = area[i];
            if (p.r == targetR && p.c == targetC) continue;
            if (std::abs(p.r - targetR) + std::abs(p.c - targetC) > 1) {
                board[p.r][p.c] = originalColor;
                changedCount++;
            }
        }
    }
    else if (bonusType == 2) {
        std::vector<Point> allBoardCells;
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (r != targetR || c != targetC) allBoardCells.push_back({ r, c });
            }
        }
        std::shuffle(allBoardCells.begin(), allBoardCells.end(), g);
        board[targetR][targetC] = 0;

        int toDestroy = std::min(4, (int)allBoardCells.size());
        for (int i = 0; i < toDestroy; ++i) {
            board[allBoardCells[i].r][allBoardCells[i].c] = 0;
        }
    }
}
