#include "Tile.h"

Tile::Tile(int X, int Y, sf::Texture& hidden, sf::Texture& revealed,
           sf::Texture& flag, sf::Texture& mine, std::vector<sf::Texture>& numbers) {
    this->X = X;
    this->Y = Y;

    revealedSprite.setTexture(revealed);
    revealedSprite.setPosition(X * 32, Y * 32);
    hiddenSprite.setTexture(hidden);
    hiddenSprite.setPosition(X * 32, Y * 32);
    flagSprite.setTexture(flag);
    flagSprite.setPosition(X * 32, Y * 32);
    mineSprite.setTexture(mine);
    mineSprite.setPosition(X * 32, Y * 32);

    for (int i = 0; i < 8; ++i) {
        numberSprites[i].setTexture(numbers[i]);
        numberSprites[i].setPosition(X * 32, Y * 32);
    }
}