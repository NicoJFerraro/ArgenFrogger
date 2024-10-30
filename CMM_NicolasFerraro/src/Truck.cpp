#include "Truck.h"

Truck::Truck(sf::Vector2u size, float posX, float posY, float speed, bool flipMovement)
{
    truck.setSize(sf::Vector2f(Global::TRUCK_WIDTH, Global::TRUCK_HEIGHT));
    truck.setFillColor(Global::TRUCK_COLOR);
    truck.setPosition(sf::Vector2f(posX, posY));

    this->speed = speed;
    this->flipMovement = flipMovement;

    originalPosX = posX;
    originalPosY = posY;
}

Truck::~Truck()
{
}

void Truck::Draw(sf::RenderWindow& window) const
{
    window.draw(truck);
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
