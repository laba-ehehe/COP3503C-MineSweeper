#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include "Board.h"
#include "LeaderboardWindow.h"

class GameWindow {
public:
    int rows;
    int cols;
    int mines;
    sf::Font& font;
    std::string player;

    GameWindow(int rows, int cols, int mines, sf::Font& font, std::string player);

    void teehee();
};

#endif // GAMEWINDOW_H