#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Truck.h"

class LevelGenerator {
public:
    // Here we input the level seed
    LevelGenerator(unsigned int seed, sf::Vector2u windowSize);

    //Generate a list of trucks for each checkpoint
    std::vector<Truck> GenerateTrucks(float checkpointY, int truckCount);

private:
    sf::Vector2u windowSize;
};

#endif
