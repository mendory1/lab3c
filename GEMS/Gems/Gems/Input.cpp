#include "Input.h"
#include "Config.h"
#include <cmath>

Input::Input() : isSelected(false), selectedCell(-1, -1) {}

void Input::resetSelection() {
    isSelected = false;
    selectedCell = sf::Vector2i(-1, -1);
}

bool Input::processClick(int mouseX, int mouseY, sf::Vector2i& outCell1, sf::Vector2i& outCell2) {
    int c = mouseX / CELL_SIZE;
    int r = mouseY / CELL_SIZE;
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return false;

    if (!isSelected) {
        selectedCell = sf::Vector2i(c, r);
        isSelected = true;
        return false;
    }
    else {
        bool isNeighbor = (std::abs(selectedCell.x - c) == 1 && selectedCell.y == r) ||
            (std::abs(selectedCell.y - r) == 1 && selectedCell.x == c);

        if (isNeighbor) {
            outCell1 = selectedCell;
            outCell2 = sf::Vector2i(c, r);
            isSelected = false;
            return true;
        }

        selectedCell = sf::Vector2i(c, r);
        return false;
    }
}
