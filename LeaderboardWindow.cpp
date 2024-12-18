#include "LeaderboardWindow.h"
#include <fstream>
#include <sstream>

LeaderboardWindow::LeaderboardWindow(sf::Font& font) : font(font) {}

std::string LeaderboardWindow::read() {
    leaderboard.clear();
    std::ifstream file("../files/leaderboard.txt");
    std::ostringstream leaders;
    std::string readline;
    int rank = 1;
    while (std::getline(file, readline) && rank <= 5) {
        size_t position = readline.find(",");
        if (position != std::string::npos) {
            std::string time = readline.substr(0, position);
            std::string name = readline.substr(position + 2);
            leaderboard[time].push_back(name);
            // Format each entry with consistent spacing
            leaders << rank << ".  " << time << "    " << name << "\n\n";
            rank++;
        }
    }
    file.close();
    return leaders.str();
}

void LeaderboardWindow::update(std::string name, std::string time) {
    leaderboard[time].push_back(name);
    auto it = leaderboard.begin();
    int idx = 0;
    std::ofstream outfile("../files/leaderboard.txt");

    for (int i = 0; i < 5 && it != leaderboard.end();) {
        if (it->second.size() > idx) {
            outfile << it->first << ", " << it->second[idx] << std::endl;
            idx++;
            i++;
        }
        else {
            idx = 0;
            it++;
        }
    }
    outfile.close();
}

void LeaderboardWindow::display(std::string leaderboardText) {
    // Create window with fixed dimensions
    sf::RenderWindow leaderboardWindow(sf::VideoMode(400, 350), "Leaderboard", sf::Style::Close);

    // Set up title text
    sf::Text leaderboardTitleText;
    leaderboardTitleText.setFont(font);
    leaderboardTitleText.setString("LEADERBOARD");
    leaderboardTitleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardTitleText.setCharacterSize(24);
    leaderboardTitleText.setFillColor(sf::Color::White);

    // Center title text properly
    sf::FloatRect titleBounds = leaderboardTitleText.getLocalBounds();
    leaderboardTitleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    leaderboardTitleText.setPosition(200, 40);

    // Set up leaderboard content text
    sf::Text leaderboardDisplay;
    leaderboardDisplay.setFont(font);
    leaderboardDisplay.setString(leaderboardText);
    leaderboardDisplay.setCharacterSize(20);
    leaderboardDisplay.setFillColor(sf::Color::White);

    // Center content text properly with more vertical space
    sf::FloatRect textBounds = leaderboardDisplay.getLocalBounds();
    leaderboardDisplay.setOrigin(textBounds.width / 2, textBounds.height / 2);
    leaderboardDisplay.setPosition(200, 200);

    while (leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.clear(sf::Color::Blue);
        leaderboardWindow.draw(leaderboardTitleText);
        leaderboardWindow.draw(leaderboardDisplay);
        leaderboardWindow.display();
    }
}