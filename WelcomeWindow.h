#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class WelcomeWindow {
public:
    std::string player;
    sf::Font& font;

    WelcomeWindow(sf::Font& font);

    std::string hellaur();
};

#endif // WELCOMEWINDOW_H