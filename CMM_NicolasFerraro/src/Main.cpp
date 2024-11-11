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

struct Checkpoint {
    float positionY;
    std::vector<Truck> trucks;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), Global::WINDOW_TITLE);
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr));

    Menu menu(window.getSize());
    PauseMenu pauseMenu(window.getSize());
    GameOverScreen gameOverScreen(window.getSize());
    bool inMenu = true;
    bool isPaused = false;
    sf::View hudView = window.getDefaultView();

    int savedSeed = seed;
    int savedLives = Global::INITIAL_LIVES;
    int savedCheckpoint = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inMenu) {
                if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.code) {
                    case sf::Keyboard::W: menu.MoveUp(); break;
                    case sf::Keyboard::S: menu.MoveDown(); break;
                    case sf::Keyboard::Enter:
                        if (menu.GetPressedItem() == Global::MENU_PLAY_OPTION) {
                            inMenu = false;
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
            LevelGenerator levelGenerator(savedSeed, window.getSize());
            std::deque<Checkpoint> checkpoints;
            int currentCheckpoint = savedCheckpoint;
            std::cout << "Saved Checkpoint: " << savedCheckpoint;

            for (int i = 0; i < Global::INITIAL_CHECKPOINTS; ++i) {
                float checkpointY = -i * Global::CHECKPOINT_DISTANCE;
                checkpoints.push_back({ checkpointY, levelGenerator.GenerateTrucks(checkpointY, 10, currentCheckpoint)});
            }

            Player frog(window.getSize(), savedLives,
                sf::Vector2f(Global::PLAYER_START_POSITION.x, checkpoints.front().positionY));
            sf::Vector2f previousPosition = frog.GetShape().getPosition();
            CameraController cameraController(sf::Vector2f(window.getSize()), frog.GetShape().getPosition());

            Timer timer(Global::TIMER_LIMIT);
            bool inGame = true;

            while (inGame) {
                sf::Event gameEvent;
                while (window.pollEvent(gameEvent)) {
                    if (gameEvent.type == sf::Event::Closed) window.close();

                    if (gameEvent.type == sf::Event::KeyReleased && gameEvent.key.code == sf::Keyboard::P) {
                        isPaused = !isPaused;
                    }

                    if (!isPaused && gameEvent.type == sf::Event::KeyReleased) {
                        frog.Move(gameEvent);
                        cameraController.Update(frog.GetShape().getPosition());
                        previousPosition = frog.GetShape().getPosition();
                    }
                }

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
                            }
                            else if (pauseMenu.GetSelectedOption() == 1) {
                                isPaused = false;
                            }
                        }
                    }
                    window.clear();
                    pauseMenu.Draw(window);
                }
                else {
                    timer.Update();
                    if (timer.IsTimeUp()) {
                        if (!frog.LostLife(window.getSize(), checkpoints[0].positionY))
                            cameraController.CenterOnPlayer(frog.GetShape().getPosition());
                        else {
                            inGame = false;
                            inMenu = true;
                        }
                        timer.Restart();
                    }

                    if (frog.GetShape().getPosition().y < checkpoints[1].positionY) {
                        checkpoints.pop_front();
                        ++currentCheckpoint;
                        float newCheckpointY = checkpoints.back().positionY - Global::CHECKPOINT_DISTANCE;
                        checkpoints.push_back({ newCheckpointY, levelGenerator.GenerateTrucks(newCheckpointY, 10, currentCheckpoint)});
                        timer.Restart();
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
                    frog.Draw(window);

                    for (const auto& checkpoint : checkpoints) {
                        for (const auto& truck : checkpoint.trucks) {
                            truck.Draw(window);
                        }
                        sf::RectangleShape finishLine(sf::Vector2f(window.getSize().x, Global::FINISH_LINE_THICKNESS));
                        finishLine.setPosition(0, checkpoint.positionY);
                        finishLine.setFillColor(Global::FINISH_LINE_COLOR);
                        window.draw(finishLine);
                    }

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

                    if (collision) {
                        if (!frog.LostLife(window.getSize(), checkpoints[0].positionY))
                            cameraController.CenterOnPlayer(frog.GetShape().getPosition());
                        else {
                            inGame = false;
                            inMenu = false;
                        }
                    }
                }
                window.display();
            }

            if (!inMenu) {
                while (!inMenu) {
                    sf::Event gameOverEvent;
                    while (window.pollEvent(gameOverEvent)) {
                        if (gameOverEvent.type == sf::Event::Closed) window.close();
                    }

                    gameOverScreen.Draw(window);

                    if (gameOverEvent.type == sf::Event::KeyReleased) {
                        if (gameOverEvent.key.code == sf::Keyboard::W) gameOverScreen.MoveUp();
                        else if (gameOverEvent.key.code == sf::Keyboard::S) gameOverScreen.MoveDown();
                        else if (gameOverEvent.key.code == sf::Keyboard::Enter) {
                            if (gameOverScreen.GetPressedItem() == 0) {
                                inMenu = true;
                                savedLives = Global::INITIAL_LIVES;
                                savedCheckpoint = 1;
                            }
                            else if (gameOverScreen.GetPressedItem() == 1) {
                                window.close();
                            }
                        }
                    }

                    window.display();
                }
            }
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
