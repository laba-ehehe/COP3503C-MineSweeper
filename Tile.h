#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
public:
    sf::Sprite hiddenSprite;
    sf::Sprite revealedSprite;
    sf::Sprite numberSprites[8];
    sf::Sprite flagSprite;
    sf::Sprite mineSprite;

    int X;
    int Y;
    int adjacent = 0;
    bool isMine = false;
    bool isOver = false;
    bool isRevealed = false;
    bool isFlagged = false;

    Tile(int X, int Y, sf::Texture& hidden, sf::Texture& revealed,
         sf::Texture& flag, sf::Texture& mine, std::vector<sf::Texture>& numbers);
};

#endif // TILE_H