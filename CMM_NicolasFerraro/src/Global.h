#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


namespace Global {

    // Window
    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;
    const std::string WINDOW_TITLE = "ArgenFrogger";

    // Menu
    const std::string GAME_TITLE = "";
    const int TITLE_FONT_SIZE = 70;
    const sf::Color TITLE_COLOR = sf::Color::White;
    const float TITLE_POSITION_Y = 50.0f;

    const std::string MENU_OPTION_PLAY = "Nuevo Juego";
    const std::string MENU_OPTION_SAVED_OPTION = "Cargar Partida";
    const std::string MENU_OPTION_EXIT = "Salir";
    const std::string PAUSE_OPTION_RESUME = "Volver al Juego";
    const std::string PAUSE_OPTION_EXIT = "Guardar y Salir";

    const int MENU_PLAY_OPTION = 0;
    const int MENU_PLAY_SAVED_OPTION = 1;
    const int MENU_EXIT_OPTION = 2;

    const int MENU_ITEM_FONT_SIZE = 50;
    const sf::Color MENU_ITEM_COLOR = sf::Color::White;
    const sf::Color MENU_SELECTED_COLOR = sf::Color::Yellow;
    const float MENU_ITEM_START_Y = 400.0f;
    const float MENU_ITEM_SPACING = 60.0f;

    // Checkpoints
    const float CHECKPOINT_DISTANCE = 1000.0f;
    const int INITIAL_CHECKPOINTS = 3;

    // Player
    const int INITIAL_LIVES = 3;
    const float PLAYER_SIZE = 40.0f;
    const float PLAYER_MOVE_OFFSET = 60.0f;
    const float PLAYER_HEIGHT = 40.0f;
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
    const sf::Color HUD_TEXT_COLOR = sf::Color::Yellow;
    const sf::Color LITTLE_TIMELEFT_TEXT_COLOR = sf::Color::Red;

    // Finish line
    const float FINISH_LINE_THICKNESS = 5.0f;
    const sf::Color FINISH_LINE_COLOR = sf::Color::White;

    // Trucks
    struct TruckData {
        sf::Vector2u textureSize;
        sf::Vector2u rect;
        sf::Vector2u truckSize;

    };

    const std::vector<TruckData> TRUCKS = {
        {{16, 9}, {0, 0}, {60, 36}},
        {{16, 10}, {0, 9}, {60, 40}},
        {{16, 12}, {0, 19}, {60, 48}},
        {{16, 13}, {0, 31}, {60, 52}},
        {{32, 13}, {0, 44}, {120, 52}}
    };

    const float TRUCK_WIDTH = 120.0f;
    const float TRUCK_HEIGHT = 52.0f;
    const sf::Color TRUCK_COLOR = sf::Color::Red;
    const float TRUCK_BASE_SPEED = 0.1f;
    const int TRUCK_SPEED_RANGE = 1;
    const float TRUCK_RESTRICTED_RANGE = 100.0f;
    const int TRUCK_POSITION_RANGE = 600;
    const int TRUCK_POSITION_OFFSET = 300;
    const int TRUCK_RAIL_SIZE = 70;

    //Save
    const std::string SAVEGAME_PATH = "C:\\Users\\nicol\\Documents\\ArgenFroggerData\\save.xml";

    //Sprites
    const std::string FROG_SPRITE_PATH = "res\\sprites\\Frogger.png";
    const std::string TRUCK_SPRITE_PATH = "res\\sprites\\Trucks.png";
    const std::string TRUCKFLIPPED_SPRITE_PATH = "res\\sprites\\TrucksFlipped.png";
    const std::string TILEMAP_SPRITE_PATH = "res\\sprites\\Route-Tiles.png";
    const std::string FROG_DEATH_SPRITE_PATH = "res\\sprites\\AnimationDeath.png";

    //SFX
    const std::string SFX_CHECKPOINTMESSI = "res\\sfx\\messi-higher.wav";
    const std::string SFX_CHECKPOINTWIN = "res\\sfx\\checkpointwin.wav";
    const std::string SFX_TIMELEFT = "res\\sfx\\timeleft.wav";
    const std::string SFX_BUTTONMOVE = "res\\sfx\\buttonmove.wav";
    const std::string SFX_BUTTONPRESS = "res\\sfx\\buttonpress.wav";
    const std::string SFX_FROGMOVE = "res\\sfx\\frogmove.wav";
    const std::string SFX_GAMEOVER = "res\\sfx\\gameover.wav";
    const std::string SFX_LOSELIFE = "res\\sfx\\lostlife.wav";

    //MUSIC
    const std::string MUSIC_MENU = "res\\music\\rodrigo.wav";
    const std::string MUSIC_GAMEPLAY = "res\\music\\transito-mona.wav";
}

#endif
