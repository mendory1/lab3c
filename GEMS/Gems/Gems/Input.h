#pragma once
#include <SFML/Graphics.hpp>

class Input {
private:
    sf::Vector2i selectedCell;
    bool isSelected;

public:
    Input();
    void resetSelection();

    bool processClick(int mouseX, int mouseY, sf::Vector2i& outCell1, sf::Vector2i& outCell2);

    sf::Vector2i getSelectedCell() const { return isSelected ? selectedCell : sf::Vector2i(-1, -1); }
};
