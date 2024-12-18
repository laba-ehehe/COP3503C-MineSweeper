# Minesweeper Project - COP3503C Spring 2024

## Author
- **Name:** Lan Anh Do
- **Section:** #11819
- **UFL Email:** lananhdo@ufl.edu

---

## Overview

This project implements the classic Minesweeper game using **C++** and **SFML** (Simple and Fast Multimedia Library). 

### Features

1. **Welcome Window**:
    - Prompts the player to enter their name (maximum 10 alphabetic characters).
    - Automatically formats the name to capitalize the first letter and lowercase the rest.
    - Proceeds to the game window upon valid input.

2. **Game Window**:
    - Dynamic board dimensions and mine placement based on `config.cfg`.
    - Supports tile revealing, flagging, and mine detection.
    - Displays mine counts and a timer.
    - Implements victory and defeat conditions with appropriate UI feedback.
    - Includes pause and debug modes.
    - Features a reset button to start a new game.

3. **Leaderboard**:
    - Displays the top 5 fastest game completion times from `leaderboard.txt`.
    - Updates the leaderboard upon achieving a new high score.
    - Allows viewing the leaderboard during the game.

4. **Additional Features**:
    - Timer to track game duration.
    - Mine counter to show remaining mines.
    - Responsive UI elements and game status indicators.

---

## File Information

### Source Code

The project is organized into multiple classes, each in its own header and source file:

- **Main Entry Point**:
    - `main.cpp`: Initializes the game and manages the game loop.

- **Classes and Corresponding Files**:
    - `Tile.h` and `Tile.cpp`: Defines the `Tile` class, representing each cell on the game board.
    - `Board.h` and `Board.cpp`: Defines the `Board` class, managing the grid of tiles and game logic.
    - `WelcomeWindow.h` and `WelcomeWindow.cpp`: Defines the `WelcomeWindow` class, handling the initial player name input screen.
    - `LeaderboardWindow.h` and `LeaderboardWindow.cpp`: Defines the `LeaderboardWindow` class, managing leaderboard display and updates.
    - `GameWindow.h` and `GameWindow.cpp`: Defines the `GameWindow` class, handling the main game interface and interactions.

### Assets

- **Images**:
    - Located in `../files/images/`.
    - Includes textures for tiles (`tile_hidden.png`, `tile_revealed.png`), numbers (`number_1.png` to `number_8.png`), flags (`flag.png`), mines (`mine.png`), buttons (`face_happy.png`, `face_lose.png`, `face_win.png`, `pause.png`, `play.png`, `debug.png`, `leaderboard.png`), and digits (`digits.png`).

- **Fonts**:
    - Located in `../files/`.
    - Includes `font.ttf` used for text rendering in the game.

### Configuration

- **Config File**:
    - `../files/config.cfg`: Contains the board dimensions and the number of mines.
    - Format:
        ```
        <number_of_columns>
        <number_of_rows>
        <number_of_mines>
        ```
    - Example:
        ```
        25
        16
        50
        ```

### Leaderboard

- **Leaderboard File**:
    - `../files/leaderboard.txt`: Stores the top 5 high scores.
    - Each line contains a time and a player name, separated by a comma.
    - The format is:
        ```
        MM:SS, PlayerName
        ```
    - Example:
        ```
        01:45, Alice
        02:10, Bob
        ```

---

## Build Instructions

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler that supports C++11 or higher.
- **SFML Library**: Install SFML library version 2.5 or higher.
    - Download from [SFML Website](https://www.sfml-dev.org/download.php).
    - Follow the installation guide appropriate for your operating system.

### Building the Project

#### Using Command Line

1. **Compile the Source Files**:

   Navigate to the directory containing the source files and run the following command:

    ```bash
    g++ -std=c++11 main.cpp GameWindow.cpp Board.cpp Tile.cpp WelcomeWindow.cpp LeaderboardWindow.cpp -o Minesweeper -lsfml-graphics -lsfml-window -lsfml-system
    ```

    - Ensure that the SFML libraries are correctly linked.
    - You may need to adjust the include and library paths depending on your SFML installation.

2. **Run the Executable**:

    ```bash
    ./Minesweeper
    ```

#### Using CLion

1. **Open the Project**:

    - Open CLion and select `Open` to navigate to the project directory.

2. **Configure `CMakeLists.txt`**:

    - Ensure that `CMakeLists.txt` includes the necessary configurations for SFML.
    - Example `CMakeLists.txt`:

        ```cmake
        cmake_minimum_required(VERSION 3.15)
        project(Minesweeper)

        set(CMAKE_CXX_STANDARD 11)

        find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

        include_directories(${SFML_INCLUDE_DIRS})

        add_executable(Minesweeper main.cpp GameWindow.cpp Board.cpp Tile.cpp WelcomeWindow.cpp LeaderboardWindow.cpp)

        target_link_libraries(Minesweeper sfml-graphics sfml-window sfml-system)
        ```

3. **Build and Run**:

    - Click on the `Build` menu and select `Build Project`.
    - Once built, run the project by clicking the `Run` button.

### Note on File Paths

- Ensure that all file paths in the code (e.g., for loading images, fonts, and configuration files) are correct relative to the executable.
- The provided code expects resource files to be located in `../files/` relative to the executable.

---

## Game Instructions

1. **Starting the Game**:

    - Run the executable to start the game.
    - Enter your name in the welcome window (alphabet characters only, up to 10 characters).
    - Press `Enter` to proceed to the game.

2. **Playing the Game**:

    - **Left-click** on a tile to reveal it.
    - **Right-click** on a tile to place or remove a flag.
    - Use the **Pause** button to pause or resume the game.
    - Use the **Reset** button (happy face icon) to start a new game.
    - Use the **Leaderboard** button to view the current leaderboard.

3. **Objective**:

    - Reveal all non-mine tiles without clicking on a mine.
    - Flag all the mines to help avoid clicking them.

4. **Game Over**:

    - If you click on a mine, the game ends, and all mines are revealed.
    - You can start a new game by clicking the reset button.

5. **Winning the Game**:

    - If you successfully reveal all non-mine tiles, you win the game.
    - Your completion time will be recorded and may be added to the leaderboard if it is among the top 5 times.

---