cmake_minimum_required(VERSION 3.14)
project(Project3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Tile.h
        Tile.cpp
        Board.h
        Board.cpp
        WelcomeWindow.h
        WelcomeWindow.cpp
        LeaderboardWindow.h
        LeaderboardWindow.cpp
        GameWindow.h
        GameWindow.cpp
)

add_executable(Project3 ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(Project3 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)