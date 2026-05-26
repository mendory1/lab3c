#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

void drawBoard(sf::RenderWindow& window, const int board[ROWS][COLS], const sf::Vector2i& selectedCell);
