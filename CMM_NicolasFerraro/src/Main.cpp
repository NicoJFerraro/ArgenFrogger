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

struct Checkpoint {
    float positionY;
    std::vector<Truck> trucks;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), Global::WINDOW_TITLE);
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr));

    Menu menu(window.getSize());
    bool inMenu = true;
    sf::View hudView = window.getDefaultView();

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
                            if (menu.GetPressedItem() == Global::MENU_PLAY_OPTION) inMenu = false;
                            else if (menu.GetPressedItem() == Global::MENU_EXIT_OPTION) window.close();
                            break;
                    }
                }
            }
        }

        window.clear();

        if (inMenu) {
            menu.Draw(window);
        } else {
            LevelGenerator levelGenerator(seed, window.getSize());
            std::deque<Checkpoint> checkpoints;

            int currentCheckpoint = 1;
            for (int i = 0; i < Global::INITIAL_CHECKPOINTS; ++i) {
                float checkpointY = -i * Global::CHECKPOINT_DISTANCE;
                checkpoints.push_back({ checkpointY, levelGenerator.GenerateTrucks(checkpointY, 10) });
            }

            Player frog(window.getSize(), Global::INITIAL_LIVES,
                        sf::Vector2f(Global::PLAYER_START_POSITION.x, checkpoints.front().positionY));
            sf::Vector2f previousPosition = frog.GetShape().getPosition();
            CameraController cameraController(sf::Vector2f(window.getSize()), frog.GetShape().getPosition());

            Timer timer(Global::TIMER_LIMIT);
            bool inGame = true;

            while (inGame) {
                sf::Event gameEvent;
                while (window.pollEvent(gameEvent)) {
                    if (gameEvent.type == sf::Event::Closed) window.close();
                    if (gameEvent.type == sf::Event::KeyReleased) {
                        frog.Move(gameEvent);
                        cameraController.Update(frog.GetShape().getPosition());
                        previousPosition = frog.GetShape().getPosition();
                    }
                }

                timer.Update();
                if (timer.IsTimeUp()) {
                    if (!frog.LostLife(window.getSize(), checkpoints[0].positionY))
                        cameraController.CenterOnPlayer(frog.GetShape().getPosition());
                    else { inGame = false; inMenu = true; }
                    timer.Restart();
                }

                if (frog.GetShape().getPosition().y < checkpoints[1].positionY) {
                    checkpoints.pop_front();
                    ++currentCheckpoint;
                    float newCheckpointY = checkpoints.back().positionY - Global::CHECKPOINT_DISTANCE;
                    checkpoints.push_back({ newCheckpointY, levelGenerator.GenerateTrucks(newCheckpointY, 10) });
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
                    else { inGame = false; inMenu = true; }
                }

                window.display();
            }
        }

        window.display();
    }
    return EXIT_SUCCESS;
}
