#include "GameWindow.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Tile.h"
#include "WelcomeWindow.h"

GameWindow::GameWindow(int rows, int cols, int mines, sf::Font& font, std::string player)
    : rows(rows), cols(cols), mines(mines), font(font), player(player) {}

void GameWindow::teehee() {
    int width = cols * 32;
    int height = rows * 32 + 100;

    // Load textures
    sf::Texture hidden, revealed, flag, mine;
    std::vector<sf::Texture> numbers(8);
    sf::Texture facehappy, debug, leaderboardTex, facelose, facewin, pauseTex, playTex, digits;

    if (!hidden.loadFromFile("../files/images/tile_hidden.png") ||
        !revealed.loadFromFile("../files/images/tile_revealed.png") ||
        !flag.loadFromFile("../files/images/flag.png") ||
        !mine.loadFromFile("../files/images/mine.png") ||
        !facehappy.loadFromFile("../files/images/face_happy.png") ||
        !debug.loadFromFile("../files/images/debug.png") ||
        !leaderboardTex.loadFromFile("../files/images/leaderboard.png") ||
        !facelose.loadFromFile("../files/images/face_lose.png") ||
        !facewin.loadFromFile("../files/images/face_win.png") ||
        !pauseTex.loadFromFile("../files/images/pause.png") ||
        !playTex.loadFromFile("../files/images/play.png") ||
        !digits.loadFromFile("../files/images/digits.png")) {
        return;
    }

    for (int i = 0; i < 8; ++i) {
        if (!numbers[i].loadFromFile("../files/images/number_" + std::to_string(i + 1) + ".png")) {
            return;
        }
    }

    sf::Sprite facehappySprite(facehappy), debugSprite(debug), leaderboardSprite(leaderboardTex), faceloseSprite(facelose), facewinSprite(facewin), pauseSprite(pauseTex), playSprite(playTex);

    facehappySprite.setPosition((cols / 2.0f * 32) - 32, 32 * (rows + 0.5f));
    debugSprite.setPosition((cols * 32) - 304, 32 * (rows + 0.5f));
    leaderboardSprite.setPosition((cols * 32) - 176, 32 * (rows + 0.5f));
    faceloseSprite.setPosition((cols / 2.0f * 32) - 32, 32 * (rows + 0.5f));
    facewinSprite.setPosition((cols / 2.0f * 32) - 32, 32 * (rows + 0.5f));
    pauseSprite.setPosition((cols * 32) - 240, 32 * (rows + 0.5f));
    playSprite.setPosition((cols * 32) - 240, 32 * (rows + 0.5f));

    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

    auto startTime = std::chrono::high_resolution_clock::now();
    auto pauseTime = std::chrono::high_resolution_clock::now();
    int elapsedPauseTime = 0;
    bool paused = false;

    std::map<int, sf::Sprite> digitSprites;

    for (int i = 0; i < 11; i++) {
        sf::IntRect rect((i * 21), 0, 21, 32);
        sf::Sprite sprite(digits, rect);
        digitSprites.emplace(i, sprite);
    }

    Board board(rows, cols, mines, hidden, revealed, flag, mine, numbers);
    int mineCount = mines;

    while (gameWindow.isOpen()) {
        sf::Event event;
        sf::Vector2i pixel = sf::Mouse::getPosition(gameWindow);
        sf::Vector2f mouse = gameWindow.mapPixelToCoords(pixel);

        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
                return;
            }
            if (!board.nay) {
                int x = pixel.x / 32;
                int y = pixel.y / 32;

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (pauseSprite.getGlobalBounds().contains(mouse) && !board.yay) {
                        paused = !paused;
                        if (paused) {
                            pauseTime = std::chrono::high_resolution_clock::now();
                        }
                        else {
                            auto unPause = std::chrono::high_resolution_clock::now();
                            elapsedPauseTime += std::chrono::duration_cast<std::chrono::seconds>(
                                unPause - pauseTime).count();
                        }
                    }

                    if (!paused) {
                        if (x >= 0 && x < cols && y >= 0 && y < rows) {
                            Tile& tile = board.tiles[y][x];
                            if (!tile.isFlagged && !tile.isMine) {
                                if (tile.adjacent == 0) {
                                    board.reveal(y, x, board.mineCount);
                                }
                                else {
                                    if (!tile.isRevealed) {
                                        tile.isRevealed = true;
                                        board.mineCount += 1;
                                    }
                                }
                            }

                            if (!tile.isFlagged) {
                                tile.isRevealed = true;
                            }
                            if (tile.isMine) {
                                tile.isRevealed = true;
                                board.nay = true;
                                paused = true;
                                pauseTime = std::chrono::high_resolution_clock::now();
                            }

                            bool won = true;
                            for (int i = 0; i < rows && won; i++) {
                                for (int j = 0; j < cols; j++) {
                                    if (!board.tiles[i][j].isMine && !board.tiles[i][j].isRevealed) {
                                        won = false;
                                        break;
                                    }
                                }
                            }

                            board.yay = won;

                            if (board.yay) {
                                paused = true;
                                pauseTime = std::chrono::high_resolution_clock::now();
                                for (int i = 0; i < rows; i++) {
                                    for (int j = 0; j < cols; j++) {
                                        if (board.tiles[i][j].isMine) {
                                            board.tiles[i][j].isFlagged = true;
                                            mineCount = 0;
                                        }
                                    }
                                }
                                int total = std::chrono::duration_cast<std::chrono::seconds>(
                                    pauseTime - startTime).count() - elapsedPauseTime;
                                int min = total / 60;
                                int sec = total % 60;
                                std::string curr_time = std::to_string(min / 10) + std::to_string(min % 10) + ":" +
                                    std::to_string(sec / 10) + std::to_string(sec % 10);

                                LeaderboardWindow leaderboardWindow(font);
                                leaderboardWindow.read();
                                leaderboardWindow.update(player, curr_time);
                            }
                        }
                        if (debugSprite.getGlobalBounds().contains(mouse)) {
                            board.debug = !board.debug;
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                    if (!paused) {
                        int x_idx = pixel.x / 32;
                        int y_idx = pixel.y / 32;

                        if (x_idx >= 0 && x_idx < cols && y_idx >= 0 && y_idx < rows) {
                            Tile& tile = board.tiles[y_idx][x_idx];
                            if (!tile.isRevealed) {
                                tile.isFlagged = !tile.isFlagged;
                                if (tile.isFlagged)
                                    mineCount--;
                                else
                                    mineCount++;
                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (facehappySprite.getGlobalBounds().contains(mouse)) {
                    mineCount = mines;
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            Tile& tile = board.tiles[i][j];
                            tile.isRevealed = false;
                            tile.isFlagged = false;
                            tile.isMine = false;
                        }
                    }
                    board.place_mines(rows, cols, mines);
                    board.calculate_adjacent_mines();
                    board.nay = false;
                    board.yay = false;
                    paused = false;
                    elapsedPauseTime = 0;
                    startTime = std::chrono::high_resolution_clock::now();
                }

                if (leaderboardSprite.getGlobalBounds().contains(mouse)) {
                    paused = true;
                    pauseTime = std::chrono::high_resolution_clock::now();

                    LeaderboardWindow leaderboardWindow(font);
                    std::string leaderboardtxt = leaderboardWindow.read();
                    leaderboardWindow.display(leaderboardtxt);

                    auto unPause = std::chrono::high_resolution_clock::now();
                    elapsedPauseTime += std::chrono::duration_cast<std::chrono::seconds>(
                        unPause - pauseTime).count();
                    paused = false;
                }
            }
        }
        gameWindow.clear(sf::Color::White);

        int total;
        if (paused) {
            total = std::chrono::duration_cast<std::chrono::seconds>(pauseTime - startTime).count() - elapsedPauseTime;
        }
        else {
            total = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() - elapsedPauseTime;
        }

        if (total < 0) total = 0;
        int min = total / 60;
        int sec = total % 60;
        int min1 = min / 10;
        int min2 = min % 10;
        int sec1 = sec / 10;
        int sec2 = sec % 10;

        digitSprites[min1].setPosition(cols * 32 - 97, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[min1]);
        digitSprites[min2].setPosition(cols * 32 - 76, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[min2]);
        digitSprites[sec1].setPosition(cols * 32 - 54, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[sec1]);
        digitSprites[sec2].setPosition(cols * 32 - 33, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[sec2]);

        int mineCount1 = std::abs(mineCount) / 100;
        int mineCount2 = (std::abs(mineCount) / 10) % 10;
        int mineCount3 = std::abs(mineCount) % 10;

        if (mineCount < 0) {
            digitSprites[10].setPosition(12, 32 * (rows + 0.5f) + 16);
            gameWindow.draw(digitSprites[10]);
        }

        digitSprites[mineCount1].setPosition(33, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[mineCount1]);
        digitSprites[mineCount2].setPosition(54, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[mineCount2]);
        digitSprites[mineCount3].setPosition(75, 32 * (rows + 0.5f) + 16);
        gameWindow.draw(digitSprites[mineCount3]);

        board.draw(gameWindow, paused);

        if (board.nay) {
            gameWindow.draw(faceloseSprite);
        }
        else if (board.yay) {
            gameWindow.draw(facewinSprite);
        }
        else {
            gameWindow.draw(facehappySprite);
        }

        if (paused && !board.nay) {
            gameWindow.draw(playSprite);
        }
        else {
            gameWindow.draw(pauseSprite);
        }
        gameWindow.draw(debugSprite);
        gameWindow.draw(leaderboardSprite);

        gameWindow.display();
    }
}