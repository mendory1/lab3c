#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>

Game::Game() : isSelected(false), selectedCell(-1, -1) {
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
    int c = mouseX / CELL_SIZE;
    int r = mouseY / CELL_SIZE;

    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return;

    if (!isSelected) {
        selectedCell = sf::Vector2i(c, r);
        isSelected = true;
    }
    else {
        if ((std::abs(selectedCell.x - c) == 1 && selectedCell.y == r) ||
            (std::abs(selectedCell.y - r) == 1 && selectedCell.x == c)) {

            std::swap(board[r][c], board[selectedCell.y][selectedCell.x]);

            bool marked[ROWS][COLS] = { false };
            if (!findMatches(marked)) {
                std::swap(board[r][c], board[selectedCell.y][selectedCell.x]);
            }
        }
        isSelected = false;
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

std::vector<Point> Game::getValidNeighborsInRadius3(int startR, int startC) {
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

void Game::triggerInstantBonus(int targetR, int targetC, int bonusType, int originalColor) {
    std::random_device rd;
    std::mt19937 g(rd());

    if (bonusType == 1) {
        board[targetR][targetC] = originalColor;

        auto area = getValidNeighborsInRadius3(targetR, targetC);
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

void Game::processDestruction() {
    bool marked[ROWS][COLS] = { false };
    if (!findMatches(marked)) return;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (marked[r][c]) {
                int origColor = board[r][c];
                board[r][c] = 0;

                if (std::rand() % 100 < 15) {
                    auto area = getValidNeighborsInRadius3(r, c);
                    if (!area.empty()) {
                        Point target = area[std::rand() % area.size()];
                        int bonusType = (std::rand() % 2) + 1;

                        triggerInstantBonus(target.r, target.c, bonusType, origColor);
                    }
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
