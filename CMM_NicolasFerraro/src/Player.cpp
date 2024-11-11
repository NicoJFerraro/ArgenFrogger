#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2u size, unsigned int lifesAmount, sf::Vector2f initialPosition)
    : lifes(lifesAmount)
{
    frog.setSize(sf::Vector2f(Global::PLAYER_SIZE, Global::PLAYER_SIZE));
    frog.setPosition(initialPosition);

    if (!heartTexture.loadFromFile(Global::HEART_TEXTURE_PATH)) {
        std::cerr << "Error loading heart texture" << std::endl;
    }

    heartSprite.setTexture(heartTexture);
    heartSprite.setScale(Global::HEART_SCALE_X / heartTexture.getSize().x, Global::HEART_SCALE_Y / heartTexture.getSize().y);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(frog);
}

void Player::DrawLives(sf::RenderWindow& window) {
    for (unsigned int i = 0; i < lifes; ++i) {
        heartSprite.setPosition(Global::HEART_POSITION_X + (i + 1) * Global::HEART_SPACING, Global::HEART_POSITION_Y);
        window.draw(heartSprite);
    }
}

void Player::Move(sf::Event event) {
    if (sf::Keyboard::Key::Left == event.key.code || sf::Keyboard::Key::A == event.key.code) {
        frog.move(-Global::PLAYER_MOVE_OFFSET, 0);
    }
    else if (sf::Keyboard::Key::Right == event.key.code || sf::Keyboard::Key::D == event.key.code) {
        frog.move(Global::PLAYER_MOVE_OFFSET, 0);
    }
    else if (sf::Keyboard::Key::Up == event.key.code || sf::Keyboard::Key::W == event.key.code) {
        frog.move(0, -Global::PLAYER_MOVE_OFFSET);
    }
    else if (sf::Keyboard::Key::Down == event.key.code || sf::Keyboard::Key::S == event.key.code) {
        frog.move(0, Global::PLAYER_MOVE_OFFSET);
    }
}

int Player::GetLifes()
{
    return lifes;
}

bool Player::LostLife(sf::Vector2u size, float checkpointPosition) {
    frog.setPosition(sf::Vector2f(size.x / 2, checkpointPosition - frog.getSize().y / 2));
    lifes--;
    return lifes <= 0;
}

sf::RectangleShape Player::GetShape() {
    return frog;
}
