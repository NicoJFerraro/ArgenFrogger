#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Player {
public:
    Player(sf::Vector2u size, unsigned int lifesAmount, sf::Vector2f initialPosition);
    ~Player();
    unsigned int lifes;
    bool LostLife(sf::Vector2u size, float checkpointPosition);
    void Draw(sf::RenderWindow& window);
    void DrawLives(sf::RenderWindow& window);
    void Move(sf::Event event);
    int GetLifes();
    sf::RectangleShape GetShape();

private:
    sf::RectangleShape frog;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
};
