#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Truck.h"
#include "TileMap.h"

class LevelGenerator {
public:
    LevelGenerator(unsigned int seed, sf::Vector2u windowSize);
    std::vector<Truck> GenerateTrucks(float checkpointY, int truckCount, int currentCheckpoint);
    TileMap GenerateTileMap(float checkpointY, int currentCheckpoint);

private:
    sf::Vector2u windowSize;
};
