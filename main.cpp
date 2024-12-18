#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "WelcomeWindow.h"
#include "GameWindow.h"

int main() {
    std::ifstream config("../files/config.cfg");
    int cols;
    int rows;
    int mines;

    if (!(config >> cols >> rows >> mines)) {
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        return -1;
    }

    WelcomeWindow welcomeWindow(font);
    std::string player = welcomeWindow.hellaur();
    if (player.empty()) {
        return 0;
    }

    GameWindow gameWindow(rows, cols, mines, font, player);
    gameWindow.teehee();
    return 0;
}