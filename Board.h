#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
public:
    std::vector<std::vector<Tile>> tiles;
    bool debug = false;
    bool nay = false; // Game over flag
    bool yay = false; // Win flag
    int mineCount = 0;
    int rows;
    int cols;

    Board(int rows, int cols, int mines, sf::Texture& hidden, sf::Texture& revealed,
          sf::Texture& flag, sf::Texture& mine, std::vector<sf::Texture>& numbers);

    void place_mines(int rows, int cols, int mines);
    void draw(sf::RenderWindow& gameWindow, bool paused);
    void calculate_adjacent_mines();
    void reveal(int row, int col, int& notMine);
};

#endif // BOARD_H