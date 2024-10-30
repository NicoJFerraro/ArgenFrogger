#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace Global {

    // Window
    const unsigned int WINDOW_WIDTH = 2560;
    const unsigned int WINDOW_HEIGHT = 1440;
    const std::string WINDOW_TITLE = "ArgenFrogger";

    // Menu
    const int MENU_PLAY_OPTION = 0;
    const int MENU_EXIT_OPTION = 1;

    const std::string GAME_TITLE = "ArgenFrogger";
    const int TITLE_FONT_SIZE = 70;
    const sf::Color TITLE_COLOR = sf::Color::White;
    const float TITLE_POSITION_Y = 50.0f;

    const std::string MENU_OPTION_PLAY = "Jugar";
    const std::string MENU_OPTION_EXIT = "Salir";
    const int MENU_ITEM_FONT_SIZE = 50;
    const sf::Color MENU_ITEM_COLOR = sf::Color::White;
    const sf::Color MENU_SELECTED_COLOR = sf::Color::Red;
    const float MENU_ITEM_START_Y = 150.0f;
    const float MENU_ITEM_SPACING = 60.0f;

    // Checkpoints
    const float CHECKPOINT_DISTANCE = 1000.0f;
    const int INITIAL_CHECKPOINTS = 3;

    // Player
    const int INITIAL_LIVES = 3;
    const float PLAYER_SIZE = 80.0f;
    const float PLAYER_MOVE_OFFSET = 80.0f;
    const float PLAYER_HEIGHT = 120.0f;
    const sf::Vector2f PLAYER_START_POSITION(WINDOW_WIDTH / 2, 0);

    // Lives
    const std::string HEART_TEXTURE_PATH = "res\\sprites\\heart.png";
    const float HEART_SCALE_X = 34.0f;
    const float HEART_SCALE_Y = 33.0f;
    const float HEART_POSITION_X = 0.0f;
    const float HEART_POSITION_Y = 10.0f;
    const float HEART_SPACING = 40.0f;

    // Timer
    const float TIMER_LIMIT = 30.0f;

    // Font
    const std::string FONT_PATH = "res\\Arial.ttf";
    const int FONT_SIZE = 30;

    // HUD
    const sf::Vector2f HUD_CHECKPOINT_POSITION(50, 50);
    const sf::Color HUD_TEXT_COLOR = sf::Color::White;

    // Finish line
    const float FINISH_LINE_THICKNESS = 5.0f;
    const sf::Color FINISH_LINE_COLOR = sf::Color::White;

    // Trucks
    const float TRUCK_WIDTH = 120.0f;
    const float TRUCK_HEIGHT = 60.0f;
    const sf::Color TRUCK_COLOR = sf::Color::Red;
    const float TRUCK_BASE_SPEED = 0.1f;
    const int TRUCK_SPEED_RANGE = 5;
    const float TRUCK_RESTRICTED_RANGE = 100.0f;
    const int TRUCK_POSITION_RANGE = 600;
    const int TRUCK_POSITION_OFFSET = 300;
}

#endif
