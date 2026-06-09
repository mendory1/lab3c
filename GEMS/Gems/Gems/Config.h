#pragma once
#include <SFML/Graphics.hpp>

const int ROWS = 5;
const int COLS = 5;
const int CELL_SIZE = 100;
const int PADDING = 10;

const int NUM_COLORS = 4;

inline const sf::Color Colors[] = {
    sf::Color::Black,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
};

struct Point {
    int r;
    int c;
    bool operator==(const Point& other) const { return r == other.r && c == other.c; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};
