#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Truck
{
public:
	Truck(sf::Vector2u size, float posX, float posY, float speed, bool flipMovement);
	~Truck();

	void Draw(sf::RenderWindow& window) const;

	void Move(sf::Vector2u size);
	sf::RectangleShape GetShape();

private:
	sf::RectangleShape truck;

	float originalPosX, originalPosY;
	float speed;
	bool flipMovement;
};
