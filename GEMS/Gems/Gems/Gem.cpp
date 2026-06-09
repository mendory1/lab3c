#include "Gem.h"
#include <cmath>

std::vector<Point> getNeighbors(int startR, int startC) {
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
