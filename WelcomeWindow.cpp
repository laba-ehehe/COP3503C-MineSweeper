#include "WelcomeWindow.h"
#include <cctype>

WelcomeWindow::WelcomeWindow(sf::Font& font) : font(font) {}

std::string WelcomeWindow::hellaur() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome to Minesweeper", sf::Style::Close);
    sf::Text title("WELCOME TO MINESWEEPER!", font, 30);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setFillColor(sf::Color::White);
    title.setPosition(400, 150);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);

    sf::Text prompt("Enter your name:", font, 20);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(400, 250);
    prompt.setOrigin(prompt.getLocalBounds().width / 2, prompt.getLocalBounds().height / 2);

    sf::Text input("", font, 20);
    input.setFillColor(sf::Color::Yellow);
    input.setPosition(400, 300);
    input.setOrigin(input.getLocalBounds().width / 2, input.getLocalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!player.empty()) {
                        player.pop_back();
                    }
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!player.empty()) {
                        window.close();
                        return player;
                    }
                }
                else if (std::isalpha(static_cast<char>(event.text.unicode))) {
                    if (player.length() < 10) {
                        char letter = static_cast<char>(event.text.unicode);
                        if (player.empty()) {
                            letter = std::toupper(letter);
                        }
                        else {
                            letter = std::tolower(letter);
                        }
                        player += letter;
                    }
                }
            }
        }
        input.setString(player + '|');
        input.setOrigin(input.getLocalBounds().width / 2, input.getLocalBounds().height / 2);
        window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(prompt);
        window.draw(input);
        window.display();
    }
    return "";
}