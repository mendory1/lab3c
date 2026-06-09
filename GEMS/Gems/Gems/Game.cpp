#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

Game::Game() {
    std::srand(std::time(nullptr));
    initBoard();
}

void Game::initBoard() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            do {
                board[r][c] = (std::rand() % NUM_COLORS) + 1;
            } while ((c >= 2 && board[r][c] == board[r][c - 1] && board[r][c] == board[r][c - 2]) ||
                (r >= 2 && board[r][c] == board[r - 1][c] && board[r][c] == board[r - 2][c]));
        }
    }
}

void Game::handleMouseClick(int mouseX, int mouseY) {
    sf::Vector2i cell1, cell2;

    if (input.processClick(mouseX, mouseY, cell1, cell2)) {
        std::swap(board[cell1.y][cell1.x], board[cell2.y][cell2.x]);

        bool marked[ROWS][COLS] = { false };
        if (!findMatches(marked)) {
            std::swap(board[cell1.y][cell1.x], board[cell2.y][cell2.x]);
        }
    }
}

void Game::floodFill(int r, int c, int color, bool visited[ROWS][COLS], std::vector<Point>& component) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return;
    if (visited[r][c] || board[r][c] != color || board[r][c] == 0) return;

    visited[r][c] = true;
    component.push_back({ r, c });

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };
    for (int i = 0; i < 4; ++i) {
        floodFill(r + dr[i], c + dc[i], color, visited, component);
    }
}

bool Game::findMatches(bool markedToDestroy[ROWS][COLS]) {
    bool visited[ROWS][COLS] = { false };
    bool hasMatches = false;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (!visited[r][c] && board[r][c] > 0) {
                std::vector<Point> component;
                floodFill(r, c, board[r][c], visited, component);

                if (component.size() >= 3) {
                    hasMatches = true;
                    for (const auto& pt : component) {
                        markedToDestroy[pt.r][pt.c] = true;
                    }
                }
            }
        }
    }
    return hasMatches;
}

void Game::processDestruction() {
    bool marked[ROWS][COLS] = { false };
    if (!findMatches(marked)) return;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (marked[r][c]) {
                int origColor = board[r][c];
                board[r][c] = 0;

                if (std::rand() % 100 < 15) {
                    int bonusType = (std::rand() % 2) + 1;
                    bonus.triggerInstantBonus(board, r, c, bonusType, origColor);
                }
            }
        }
    }
}

void Game::dropGems() {
    for (int c = 0; c < COLS; ++c) {
        int emptyRow = ROWS - 1;
        for (int r = ROWS - 1; r >= 0; --r) {
            if (board[r][c] != 0) {
                if (emptyRow != r) {
                    board[emptyRow][c] = board[r][c];
                    board[r][c] = 0;
                }
                emptyRow--;
            }
        }
    }
    fillEmptyCells();
}

void Game::fillEmptyCells() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] == 0) {
                board[r][c] = (std::rand() % NUM_COLORS) + 1;
            }
        }
    }
}

void Game::update() {
    bool marked[ROWS][COLS] = { false };
    while (findMatches(marked)) {
        processDestruction();
        dropGems();
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) marked[r][c] = false;
        }
    }
}
