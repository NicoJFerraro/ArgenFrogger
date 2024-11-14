#pragma once
#include "Truck.h"
#include <iostream>

Truck::Truck(float posX, float posY, float speed, bool flipMovement, sf::Vector2u textureSize, sf::Vector2u rect, sf::Vector2u truckSize)
{
    truck.setSize(sf::Vector2f(truckSize.x, truckSize.y));

    truck.setFillColor(Global::TRUCK_COLOR);
    truck.setPosition(sf::Vector2f(posX, posY));

    this->speed = speed;
    this->flipMovement = flipMovement;
    this->textureSize = textureSize;
    this->rect = rect;
    this->truckSize = truckSize;

    originalPosX = posX;
    originalPosY = posY;

    if (flipMovement)
    {
        if (!truckTexture.loadFromFile(Global::TRUCKFLIPPED_SPRITE_PATH)) {
            std::cerr << "Error loading player spritesheet" << std::endl;
        }
    }
    else
    {
        if (!truckTexture.loadFromFile(Global::TRUCK_SPRITE_PATH)) {
            std::cerr << "Error loading player spritesheet" << std::endl;
        }
    }

    sprite.setTextureRect(sf::IntRect(rect.x, rect.y, textureSize.x, textureSize.y));
    sprite.setTexture(truckTexture);
    sprite.setScale(truckSize.x / textureSize.x, truckSize.y / textureSize.y);
}

Truck::~Truck()
{
}

void Truck::Draw(sf::RenderWindow& window)
{
    sprite.setTexture(truckTexture);
    sprite.setScale(truckSize.x / textureSize.x, truckSize.y / textureSize.y);
    sprite.setPosition(truck.getPosition());
    window.draw(sprite);
}

void Truck::Move(sf::Vector2u size)
{
    truck.move(speed * (1 - 2 * flipMovement), 0);

    if (!flipMovement && truck.getPosition().x > size.x)
    {
        truck.setPosition(sf::Vector2f(0 - truck.getSize().x / 2, originalPosY));
    }
    else if (flipMovement && truck.getPosition().x + truck.getSize().x < 0)
    {
        truck.setPosition(sf::Vector2f(size.x, originalPosY));
    }
}

sf::RectangleShape Truck::GetShape()
{
    return truck;
}
