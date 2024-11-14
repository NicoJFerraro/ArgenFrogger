#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Player {
public:
    Player(sf::Vector2u size, unsigned int lifesAmount, sf::Vector2f initialPosition);
    ~Player();

    unsigned int lifes;
    bool LostLife(sf::Vector2u size, float checkpointPosition);
    void ResetPositionAfterDeath();
    void Draw(sf::RenderWindow& window);
    void DrawLives(sf::RenderWindow& window);
    void Move(sf::Event event);
    void ForcePosition(sf::Vector2f pos);
    int GetLifes();
    sf::RectangleShape GetShape();
    void UpdateAnimation(int dir);
    void Update(float deltaTime);
    bool IsDeadAnimationPlaying();

private:
    sf::RectangleShape frog;
    sf::Sprite sprite;
    sf::Texture playerTexture;
    sf::Vector2i frameSize;
    sf::Vector2i deathFrameSize;
    sf::Texture deathTexture;

    unsigned int currentFrame;
    float animationSpeed;
    float animationTimer;

    bool isDeadAnimationPlaying;
    float deathAnimationTime;
    float deathAnimationTimer;

    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    sf::Vector2u windowSize;
    float checkpointPosition;
};
