#include "LevelGenerator.h"
#include <cstdlib>
#include <ctime>
#include "tinyxml2.h"

LevelGenerator::LevelGenerator(unsigned int seed, sf::Vector2u windowSize) : windowSize(windowSize) {
    srand(seed);
}

std::vector<Truck> LevelGenerator::GenerateTrucks(float checkpointY, int truckCount, int currentCheckpoint) {
    std::vector<Truck> trucks;
    float minY = checkpointY - Global::TRUCK_RESTRICTED_RANGE;
    float maxY = checkpointY + Global::TRUCK_RESTRICTED_RANGE;

    for (int i = 0; i < truckCount; ++i) {
        float posY;

        // This creates a prohibited range for the truck to spawn
        do {
            posY = checkpointY + (rand() % Global::TRUCK_POSITION_RANGE - Global::TRUCK_POSITION_OFFSET);
        } while (posY > minY && posY < maxY);

        // Use the currentCheckpoint to add to the trucks base speed, so the random is applied to de speed
        float speed = Global::TRUCK_BASE_SPEED + (currentCheckpoint * 1.3) + static_cast<float>(rand() % Global::TRUCK_SPEED_RANGE) / 10.0f;
        bool flipMovement = rand() % 2;
        trucks.emplace_back(windowSize, 0, posY, speed, flipMovement);
    }

    return trucks;
}
