#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Player.h"
#include "CameraController.h"
#include "Truck.h"
#include "LevelGenerator.h"
#include "Menu.h"
#include "Timer.h"
#include <vector>
#include <deque>
#include "PauseMenu.h"
#include "SaveManager.cpp"
#include <filesystem>
#include "GameOverScreen.h"
#include "AudioManager.h"


struct Checkpoint {
    float positionY;
    std::vector<Truck> trucks;
    TileMap tileMap;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), Global::WINDOW_TITLE);
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr));

    Menu menu(window.getSize());
    PauseMenu pauseMenu(window.getSize());
    GameOverScreen gameOverScreen(window.getSize());
    bool inMenu = true;
    bool isPaused = false;
    bool isGameOver = false;
    sf::View hudView = window.getDefaultView();

    int savedSeed = seed;
    int savedLives = Global::INITIAL_LIVES;
    int savedCheckpoint = 1;
    AudioManager::Instance().PlayMusic(Global::MUSIC_MENU);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inMenu) {
                if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        menu.MoveUp();
                        AudioManager::Instance().PlaySFX(Global::SFX_BUTTONMOVE);
                        break;

                    case sf::Keyboard::S: 
                        menu.MoveDown();
                        AudioManager::Instance().PlaySFX(Global::SFX_BUTTONMOVE);
                        break;

                    case sf::Keyboard::Enter:
                        AudioManager::Instance().PlaySFX(Global::SFX_BUTTONPRESS);
                        if (menu.GetPressedItem() == Global::MENU_PLAY_OPTION) {
                            inMenu = false;
                            savedSeed = static_cast<unsigned int>(std::time(nullptr));
                            savedLives = Global::INITIAL_LIVES;
                            savedCheckpoint = 1;
                        }
                        else if (menu.GetPressedItem() == Global::MENU_PLAY_SAVED_OPTION) {
                            if (std::filesystem::exists(Global::SAVEGAME_PATH)) {
                                std::cout << "FILE EXISTS";
                                if (SaveManager::LoadGame(Global::SAVEGAME_PATH, savedSeed, savedLives, savedCheckpoint)) {                                  
                                    inMenu = false;
                                }
                                else {
                                    std::cerr << "Error loading saved game." << std::endl;                                 
                                }
                            }
                            else {
                                std::cerr << "No saved game found." << std::endl;
                            }
                        }
                        else if (menu.GetPressedItem() == Global::MENU_EXIT_OPTION) {
                            window.close();
                        }
                        break;
                    }
                }
            }
        }

        window.clear();

        if (inMenu) {
            menu.Draw(window);
        }
        else {
            AudioManager::Instance().PlayMusic(Global::MUSIC_GAMEPLAY);
            Checkpoint oldCheckpoint;
            LevelGenerator levelGenerator(savedSeed, window.getSize());
            std::deque<Checkpoint> checkpoints;

            int currentCheckpoint = savedCheckpoint;

            for (int i = 0; i < Global::INITIAL_CHECKPOINTS; ++i) {
                float checkpointY = -i * Global::CHECKPOINT_DISTANCE;
                std::vector<Truck> trucks = levelGenerator.GenerateTrucks(checkpointY, 10, currentCheckpoint);
                TileMap tileMap = levelGenerator.GenerateTileMap(checkpointY, currentCheckpoint);
                checkpoints.push_back({ checkpointY, trucks, tileMap});
            }

            Player frog(window.getSize(), savedLives,
                sf::Vector2f(Global::PLAYER_START_POSITION.x, checkpoints.front().positionY));
            sf::Vector2f previousPosition = frog.GetShape().getPosition();
            CameraController cameraController(sf::Vector2f(window.getSize()), frog.GetShape().getPosition());

            Timer timer(Global::TIMER_LIMIT);
            bool inGame = true;
            sf::Clock clock;
            while (inGame) {
                sf::Event gameEvent;

                float deltaTime = clock.restart().asSeconds();

                while (window.pollEvent(gameEvent)) {
                    if (gameEvent.type == sf::Event::Closed) window.close();

                    if (gameEvent.type == sf::Event::KeyReleased && gameEvent.key.code == sf::Keyboard::P) {
                        isPaused = !isPaused;
                    }

                    if (!frog.IsDeadAnimationPlaying() && !isPaused && gameEvent.type == sf::Event::KeyReleased) {
                        AudioManager::Instance().PlaySFX(Global::SFX_FROGMOVE);
                        frog.Move(gameEvent);
                        cameraController.Update(frog.GetShape().getPosition());
                        previousPosition = frog.GetShape().getPosition();
                    }
                }

                frog.Update(deltaTime);

                timer.PauseTimer(isPaused);
                if (isPaused) {
                    if (gameEvent.type == sf::Event::KeyReleased) {
                        if (gameEvent.key.code == sf::Keyboard::W) pauseMenu.MoveUp();
                        else if (gameEvent.key.code == sf::Keyboard::S) pauseMenu.MoveDown();
                        else if (gameEvent.key.code == sf::Keyboard::Enter) {
                            if (pauseMenu.GetSelectedOption() == 0) {
                                SaveManager::SaveGame(Global::SAVEGAME_PATH, savedSeed, frog.GetLifes(), currentCheckpoint);
                                inGame = false;
                                inMenu = true;
                                isPaused = false;
                                AudioManager::Instance().PlayMusic(Global::MUSIC_MENU);
                            }
                            else if (pauseMenu.GetSelectedOption() == 1) {
                                isPaused = false;
                            }
                        }
                    }
                    window.clear();
                    pauseMenu.Draw(window);
                    timer.InPauseUpdate();
                }
                else {
                    timer.Update();

                    if (timer.IsTimeUp()) {
                        if (!frog.LostLife(window.getSize(), checkpoints[0].positionY))
                        {
                            AudioManager::Instance().PlaySFX(Global::SFX_LOSELIFE);
                            cameraController.CenterOnPlayer(frog.GetShape().getPosition());
                        }
                        else {
                            AudioManager::Instance().PlaySFX(Global::SFX_GAMEOVER);
                            inGame = false;
                            inMenu = true;
                        }
                        timer.Restart();
                    }

                    if (frog.GetShape().getPosition().y < checkpoints[1].positionY) {
                        //Reached new checkpoint
                        oldCheckpoint = checkpoints.front();
                        checkpoints.pop_front();
                        ++currentCheckpoint;
                        float newCheckpointY = checkpoints.back().positionY - Global::CHECKPOINT_DISTANCE;
                        std::vector<Truck> trucks = levelGenerator.GenerateTrucks(newCheckpointY, 10, currentCheckpoint);
                        TileMap tileMap = levelGenerator.GenerateTileMap(newCheckpointY, currentCheckpoint);
                        checkpoints.push_back({ newCheckpointY, trucks, tileMap});
                        timer.Restart();
                        AudioManager::Instance().PlaySFX(Global::SFX_CHECKPOINTWIN);
                        AudioManager::Instance().PlaySFX(Global::SFX_CHECKPOINTMESSI);
                    }

                    bool collision = false;
                    for (auto& checkpoint : checkpoints) {
                        for (auto& truck : checkpoint.trucks) {
                            truck.Move(window.getSize());
                            if (frog.GetShape().getGlobalBounds().intersects(truck.GetShape().getGlobalBounds())) {
                                collision = true;
                                break;
                            }
                        }
                        if (collision) break;
                    }

                    window.clear();
                    cameraController.ApplyToWindow(window);
                    window.draw(oldCheckpoint.tileMap);
                    for (auto& checkpoint : checkpoints) {
                        //Draw Tilemaps
                        window.draw(checkpoint.tileMap);

                        //Draw Trucks
                        for (auto& truck : checkpoint.trucks) {
                            truck.Draw(window);
                        }
                        
                        //Draw FinishLine Sprite
                        sf::Texture sideWalkTexture;
                        sf::Sprite sideWalkSprite;

                        if (!sideWalkTexture.loadFromFile("res\\sprites\\SidewalkBig.png"))
                        {
                            std::cerr << "Error loading heart texture" << std::endl;
                        }

                        sideWalkSprite.setTexture(sideWalkTexture);
                        sideWalkSprite.setScale(sideWalkTexture.getSize().x, Global::TRUCK_RAIL_SIZE / sideWalkTexture.getSize().y);
                        sideWalkSprite.setPosition(0, checkpoint.positionY);
                        window.draw(sideWalkSprite);
                    }

                    frog.Draw(window);             
                    window.setView(hudView);
                    sf::Font font;
                    font.loadFromFile(Global::FONT_PATH);

                    timer.Draw(window, font);
                    frog.DrawLives(window);

                    sf::Text checkpointText;
                    checkpointText.setFont(font);
                    checkpointText.setCharacterSize(Global::FONT_SIZE);
                    checkpointText.setFillColor(Global::HUD_TEXT_COLOR);
                    checkpointText.setString("Checkpoint: " + std::to_string(currentCheckpoint));
                    checkpointText.setPosition(Global::HUD_CHECKPOINT_POSITION);
                    window.draw(checkpointText);

                    if (!frog.IsDeadAnimationPlaying() && collision) {
                        if (!frog.LostLife(window.getSize(), checkpoints[0].positionY))
                        {
                            AudioManager::Instance().PlaySFX(Global::SFX_LOSELIFE);
                            cameraController.OnPlayerDeath(checkpoints[0].positionY);
                        }
                        else {
                            AudioManager::Instance().PlaySFX(Global::SFX_GAMEOVER);
                            inGame = false;
                            inMenu = false;
                            isGameOver = true;
                        }
                    }

                    sf::Vector2f frogPosition = frog.GetShape().getPosition();
                    sf::FloatRect cameraBounds = cameraController.GetCameraBounds();

                    // Limit position on X axis
                    if (frogPosition.x - frog.GetShape().getSize().x < cameraBounds.left) {
                        frogPosition.x = cameraBounds.left;
                    }
                    else if (frogPosition.x + frog.GetShape().getSize().x > cameraBounds.left + cameraBounds.width) {
                        frogPosition.x = cameraBounds.left + cameraBounds.width - frog.GetShape().getSize().x;
                    }

                    // Limit position on Y axis
                    if (frogPosition.y + frog.GetShape().getSize().y > cameraBounds.top + cameraBounds.height) {
                         frogPosition.y = cameraBounds.top + cameraBounds.height - frog.GetShape().getSize().y;
                    }

                    frog.ForcePosition(frogPosition);
                }
                window.display();
            }

           if(!inMenu)
            while (isGameOver) {
                sf::Event gameOverEvent;
                while (window.pollEvent(gameOverEvent)) {
                    if (gameOverEvent.type == sf::Event::Closed) window.close();
                    if (gameOverEvent.type == sf::Event::KeyReleased) {
                        switch (gameOverEvent.key.code) {
                        case sf::Keyboard::Enter:
                            inMenu = true;
                            isGameOver = false;
                            savedLives = Global::INITIAL_LIVES;
                            savedCheckpoint = 1;
                            AudioManager::Instance().PlayMusic(Global::MUSIC_MENU);
                            break;
                        }
                    }
                }
                gameOverScreen.Draw(window);
                window.display();
            }


        }
        window.display();
    }
    return EXIT_SUCCESS;
}
