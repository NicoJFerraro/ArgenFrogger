#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2u size, unsigned int lifesAmount, sf::Vector2f initialPosition)
    : lifes(lifesAmount), currentFrame(0), animationSpeed(0.1f), animationTimer(0.0f),
    isDeadAnimationPlaying(false), deathAnimationTime(1.0f), deathAnimationTimer(0.0f)
{
    // Configuración de la rana
    frog.setSize(sf::Vector2f(Global::PLAYER_SIZE, Global::PLAYER_SIZE));
    frog.setPosition(initialPosition);

    // Cargar el spritesheet normal del jugador
    if (!playerTexture.loadFromFile(Global::FROG_SPRITE_PATH)) {
        std::cerr << "Error loading player spritesheet" << std::endl;
    }

    // Cargar el spritesheet de la animación de muerte
    if (!deathTexture.loadFromFile(Global::FROG_DEATH_SPRITE_PATH)) {
        std::cerr << "Error loading death animation spritesheet" << std::endl;
    }

    sprite.setTexture(playerTexture);

    // Configurar tamaño de cada frame (13x13 píxeles para el sprite normal)
    frameSize = sf::Vector2i(13, 13);
    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    sprite.setScale(Global::PLAYER_SIZE / frameSize.x, Global::PLAYER_SIZE / frameSize.y);

    // Cargar la textura del corazón para las vidas
    if (!heartTexture.loadFromFile(Global::HEART_TEXTURE_PATH)) {
        std::cerr << "Error loading heart texture" << std::endl;
    }

    heartSprite.setTexture(heartTexture);
    heartSprite.setScale(Global::HEART_SCALE_X / heartTexture.getSize().x, Global::HEART_SCALE_Y / heartTexture.getSize().y);
}

Player::~Player()
{
}

void Player::Update(float deltaTime) {
    if (isDeadAnimationPlaying) {
        deathAnimationTimer += deltaTime;

        float frameDuration = deathAnimationTime / 4.0f; // 4 frames
        int frameSpacing = 1; // 1 píxel de separación entre frames
        int frameWidthWithSpacing = deathFrameSize.x;

        // Cambiar de frame si es necesario
        if (deathAnimationTimer >= frameDuration * currentFrame && currentFrame < 4) {
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidthWithSpacing, 0, deathFrameSize.x, deathFrameSize.y));
            currentFrame++;
        }

        // Finalizar la animación después de 1 segundo
        if (deathAnimationTimer >= deathAnimationTime) {
            isDeadAnimationPlaying = false;

            // Restaurar la textura normal del jugador
            sprite.setTexture(playerTexture);

            sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
            sprite.setScale(Global::PLAYER_SIZE / frameSize.x, Global::PLAYER_SIZE / frameSize.y);
            currentFrame = 0; // Reiniciar el frame

            ResetPositionAfterDeath();
        }
    }
}

bool Player::IsDeadAnimationPlaying(){
    return isDeadAnimationPlaying;
}

void Player::Move(sf::Event event) {
    if (isDeadAnimationPlaying) {
        return;  // No permitir movimiento durante la animación de muerte
    }

    int dir = 1;
    if (sf::Keyboard::Key::Left == event.key.code || sf::Keyboard::Key::A == event.key.code) {
        frog.move(-Global::PLAYER_MOVE_OFFSET, 0);
        dir = 0;
    }
    else if (sf::Keyboard::Key::Right == event.key.code || sf::Keyboard::Key::D == event.key.code) {
        frog.move(Global::PLAYER_MOVE_OFFSET, 0);
        dir = 1;
    }
    else if (sf::Keyboard::Key::Up == event.key.code || sf::Keyboard::Key::W == event.key.code) {
        frog.move(0, -Global::PLAYER_MOVE_OFFSET);
        dir = 2;
    }
    else if (sf::Keyboard::Key::Down == event.key.code || sf::Keyboard::Key::S == event.key.code) {
        frog.move(0, Global::PLAYER_MOVE_OFFSET);
        dir = 3;
    }
    UpdateAnimation(dir);
}

void Player::UpdateAnimation(int dir) {
    // El spritesheet normal tiene 4 direcciones
    int frameWidth = 13;
    sprite.setTextureRect(sf::IntRect(frameWidth * dir, 0, frameSize.x, frameSize.y));
}

void Player::Draw(sf::RenderWindow& window) {
    // Actualizar la posición del sprite para que coincida con la posición del jugador
    sprite.setPosition(frog.getPosition());
    window.draw(sprite);
}

void Player::DrawLives(sf::RenderWindow& window) {
    for (unsigned int i = 0; i < lifes; ++i) {
        heartSprite.setPosition(Global::HEART_POSITION_X + (i + 1) * Global::HEART_SPACING, Global::HEART_POSITION_Y);
        window.draw(heartSprite);
    }
}

void Player::ForcePosition(sf::Vector2f pos) {
    frog.setPosition(pos);
}

int Player::GetLifes() {
    return lifes;
}

bool Player::LostLife(sf::Vector2u size, float checkpointPosition) {

    if (isDeadAnimationPlaying) return false;
    lifes--;
    isDeadAnimationPlaying = true;
    deathAnimationTimer = 0.0f;
    currentFrame = 0;
    windowSize = size;
    this->checkpointPosition = checkpointPosition;

    // Cambiar la textura del sprite a la de animación de muerte
    sprite.setTexture(deathTexture);

    // Configurar el tamaño de cada frame de la animación de muerte (16x3 píxeles)
    deathFrameSize = sf::Vector2i(13, 13);
    sprite.setTextureRect(sf::IntRect(0, 0, deathFrameSize.x, deathFrameSize.y));
    sprite.setScale(Global::PLAYER_SIZE / deathFrameSize.x, Global::PLAYER_SIZE / deathFrameSize.y);
    sprite.setPosition(frog.getPosition());

    return lifes <= 0;
}
void Player::ResetPositionAfterDeath() {

    // Colocar la rana en el checkpoint
    frog.setPosition(sf::Vector2f(windowSize.x / 2, checkpointPosition - frog.getSize().y / 2));
}

sf::RectangleShape Player::GetShape() {
    return frog;
}
