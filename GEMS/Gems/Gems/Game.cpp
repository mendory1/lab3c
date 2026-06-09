#include "Game.h"
#include "GemFactory.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game() {
    std::srand(std::time(nullptr));
    initBoard();
}

void Game::syncIntBoard() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            intBoard[r][c] = board[r][c] ? board[r][c]->getColor() : 0;
        }
    }
}

void Game::initBoard() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            do {
                int color = (std::rand() % NUM_COLORS) + 1;
                board[r][c] = std::make_unique<RegularGem>(color);
                intBoard[r][c] = color;
            } while ((c >= 2 && intBoard[r][c] == intBoard[r][c - 1] && intBoard[r][c] == intBoard[r][c - 2]) ||
                (r >= 2 && intBoard[r][c] == intBoard[r - 1][c] && intBoard[r][c] == intBoard[r - 2][c]));
        }
    }
}

void Game::handleMouseClick(int mouseX, int mouseY) {
    sf::Vector2i cell1, cell2;

    if (input.processClick(mouseX, mouseY, cell1, cell2)) {
        std::swap(board[cell1.y][cell1.x], board[cell2.y][cell2.x]);
        syncIntBoard();

        bool marked[ROWS][COLS] = { false };
        if (!findMatches(marked)) {
            std::swap(board[cell1.y][cell1.x], board[cell2.y][cell2.x]);
            syncIntBoard();
        }
    }
}

void Game::floodFill(int r, int c, int color, bool visited[ROWS][COLS], std::vector<Point>& component) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return;
    if (visited[r][c] || intBoard[r][c] != color || intBoard[r][c] == 0) return;

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
            if (!visited[r][c] && intBoard[r][c] > 0) {
                std::vector<Point> component;
                floodFill(r, c, intBoard[r][c], visited, component);

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

    int tempBoard[ROWS][COLS];
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) tempBoard[r][c] = intBoard[r][c];
    }

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (marked[r][c] && board[r][c]) {
                board[r][c]->onDestroy(tempBoard, r, c);
                board[r][c].reset();
            }
        }
    }

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (tempBoard[r][c] == 0 && board[r][c]) {
                board[r][c].reset();
            }
            else if (board[r][c] && board[r][c]->getColor() != tempBoard[r][c]) {
                board[r][c] = std::make_unique<RegularGem>(tempBoard[r][c]);
            }
        }
    }
    syncIntBoard();
}

void Game::dropGems() {
    for (int c = 0; c < COLS; ++c) {
        int emptyRow = ROWS - 1;
        for (int r = ROWS - 1; r >= 0; --r) {
            if (board[r][c] != 0) {
                if (emptyRow != r) {
                    board[emptyRow][c] = std::move(board[r][c]);
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
            if (!board[r][c]) {
                board[r][c] = GemFactory::createRandomGem();
            }
        }
    }
    syncIntBoard();
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
