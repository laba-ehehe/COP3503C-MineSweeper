#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class LeaderboardWindow {
public:
    sf::Font& font;
    std::map<std::string, std::vector<std::string>> leaderboard;

    LeaderboardWindow(sf::Font& font);

    std::string read();
    void update(std::string name, std::string time);
    void display(std::string leaderboardText);
};

#endif // LEADERBOARDWINDOW_H