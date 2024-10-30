#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class CameraController
{
public:
    CameraController(const sf::Vector2f& size, const sf::Vector2f& targetPosition);
    ~CameraController();

    void SetInitialPosition(const sf::Vector2f& position);
    void Update(const sf::Vector2f& targetPosition);
    void CenterOnPlayer(const sf::Vector2f& playerPosition);
    void ApplyToWindow(sf::RenderWindow& window);

private:
    sf::View cameraView;
};
