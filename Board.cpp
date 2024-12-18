#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Board::Board(int rows, int cols, int mines, sf::Texture& hidden, sf::Texture& revealed,
             sf::Texture& flag, sf::Texture& mine, std::vector<sf::Texture>& numbers) {
    this->rows = rows;
    this->cols = cols;
    tiles.resize(rows, std::vector<Tile>());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tiles[i].emplace_back(j, i, hidden, revealed, flag, mine, numbers);
        }
    }
    place_mines(rows, cols, mines);
    calculate_adjacent_mines();
}

void Board::place_mines(int rows, int cols, int mines) {
    int i = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (i < mines) {
        int idx = rand() % (rows * cols);
        int x = idx % cols;
        int y = idx / cols;

        if (!tiles[y][x].isMine) {
            i++;
            tiles[y][x].isMine = true;
        }
    }
}

void Board::draw(sf::RenderWindow& gameWindow, bool paused) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile& tile = tiles[i][j];

            if (paused && !nay && !yay) {
                gameWindow.draw(tile.revealedSprite);
            }
            else {
                if (nay || yay) {
                    if (tile.isMine) {
                        gameWindow.draw(tile.revealedSprite);
                        gameWindow.draw(tile.mineSprite);
                    }
                    else {
                        if (tile.isRevealed) {
                            gameWindow.draw(tile.revealedSprite);
                            if (tile.adjacent > 0 && tile.adjacent <= 8) {
                                gameWindow.draw(tile.numberSprites[tile.adjacent - 1]);
                            }
                        }
                        else {
                            gameWindow.draw(tile.hiddenSprite);
                        }
                    }
                }
                else {
                    if (!tile.isRevealed) {
                        gameWindow.draw(tile.hiddenSprite);
                        if (tile.isFlagged) {
                            gameWindow.draw(tile.flagSprite);
                        }
                    }
                    else {
                        gameWindow.draw(tile.revealedSprite);
                        if (tile.isMine) {
                            gameWindow.draw(tile.mineSprite);
                        }
                        else if (tile.adjacent > 0 && tile.adjacent <= 8) {
                            gameWindow.draw(tile.numberSprites[tile.adjacent - 1]);
                        }
                    }
                    if (debug && tile.isMine) {
                        gameWindow.draw(tile.mineSprite);
                    }
                }
            }
        }
    }
}

void Board::calculate_adjacent_mines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int mineCount = 0;
            for (int y = std::max(0, i - 1); y <= std::min(rows - 1, i + 1); y++) {
                for (int x = std::max(0, j - 1); x <= std::min(cols - 1, j + 1); x++) {
                    if (tiles[y][x].isMine && !(y == i && x == j)) {
                        mineCount++;
                    }
                }
            }
            tiles[i][j].adjacent = mineCount;
        }
    }
}

void Board::reveal(int row, int col, int& notMine) {
    if (row < 0 || col < 0 || row >= rows || col >= cols) {
        return;
    }
    Tile& tile = tiles[row][col];
    if (tile.isRevealed || tile.isFlagged) {
        return;
    }
    tile.isRevealed = true;
    notMine++;

    if (tile.adjacent == 0 && !tile.isMine) {
        for (int y = std::max(0, row - 1); y <= std::min(rows - 1, row + 1); y++) {
            for (int x = std::max(0, col - 1); x <= std::min(cols - 1, col + 1); x++) {
                if (!(y == row && x == col)) {
                    reveal(y, x, notMine);
                }
            }
        }
    }
}