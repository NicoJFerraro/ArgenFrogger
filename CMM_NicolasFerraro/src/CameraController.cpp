#include "CameraController.h"
#include <iostream>

CameraController::CameraController(const sf::Vector2f& size, const sf::Vector2f& targetPosition)
{
    cameraView.setSize(size);

    sf::Vector2f vector(targetPosition.x, targetPosition.y - size.y / 2 + Global::PLAYER_HEIGHT);
    cameraView.setCenter(vector);
}

CameraController::~CameraController()
{
}

void CameraController::SetInitialPosition(const sf::Vector2f& position)
{
    cameraView.setCenter(position);
}

void CameraController::Update(const sf::Vector2f& targetPosition)
{
    if (targetPosition.y < cameraView.getCenter().y)
    {
        cameraView.setCenter(cameraView.getCenter().x, targetPosition.y);
    }
}

void CameraController::CenterOnPlayer(const sf::Vector2f& playerPosition)
{
    cameraView.setCenter(cameraView.getSize().x / 2, playerPosition.y - cameraView.getSize().y / 2 + Global::PLAYER_HEIGHT);
}

void CameraController::OnPlayerDeath(float checkpointPosition)
{
    cameraView.setCenter(cameraView.getSize().x / 2, checkpointPosition);
}

void CameraController::ApplyToWindow(sf::RenderWindow& window)
{
    window.setView(cameraView);
}

sf::FloatRect CameraController::GetCameraBounds()
{
    sf::FloatRect cameraBounds = cameraView.getViewport();
    cameraBounds.left = cameraView.getCenter().x - (cameraView.getSize().x / 2);
    cameraBounds.top = cameraView.getCenter().y - (cameraView.getSize().y / 2);
    cameraBounds.width = cameraView.getSize().x;
    cameraBounds.height = cameraView.getSize().y;
    return cameraBounds;
}
