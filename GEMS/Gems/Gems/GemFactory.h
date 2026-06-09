#pragma once
#include <memory>
#include <cstdlib>
#include "RegularGem.h"
#include "ColorBonusGem.h"
#include "BombBonusGem.h"

class GemFactory {
public:
    static std::unique_ptr<Gem> createRandomGem(int forceColor = 0) {
        int color = (forceColor > 0) ? forceColor : (std::rand() % NUM_COLORS) + 1;

        if (std::rand() % 100 < 15) {
            if (std::rand() % 2 == 0) {
                return std::make_unique<ColorBonusGem>(color);
            }
            else {
                return std::make_unique<BombBonusGem>(color);
            }
        }
        return std::make_unique<RegularGem>(color);
    }
};
