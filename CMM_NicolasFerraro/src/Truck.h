#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Truck
{
public:
	Truck(float posX, float posY, float speed, bool flipMovement, sf::Vector2u textureSize, sf::Vector2u rect, sf::Vector2u truckSize);
	~Truck();

	void Draw(sf::RenderWindow& window);

	void Move(sf::Vector2u size);
	sf::RectangleShape GetShape();
	// Variables de animación
	sf::Sprite sprite;
	sf::Texture truckTexture;
	sf::Vector2i frameSize;

private:
	sf::RectangleShape truck;
	sf::Vector2u textureSize, rect, truckSize;
	float originalPosX, originalPosY;
	float speed;
	bool flipMovement;
};
