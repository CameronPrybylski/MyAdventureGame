cmake_minimum_required(VERSION 3.15)
project(MyAdventureGame)

add_executable(MyAdventureGame
    src/main.cpp
    src/Level.cpp
    src/GameOver.cpp
    src/Player.cpp
    src/Sword.cpp
    src/Obstacle.cpp
    src/Enemy.cpp
    # Add your game source files here
)

target_include_directories(MyAdventureGame
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include          #Game Headers   
)

target_link_libraries(MyAdventureGame PRIVATE Engine)

