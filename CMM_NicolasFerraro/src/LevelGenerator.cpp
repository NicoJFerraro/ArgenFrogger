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
    
    //Usamos el Truck rail size, para que cada camion se separe en el eje Y creando la ilusion de que es un carril
    int truckSpawnPosition = checkpointY + Global::TRUCK_POSITION_OFFSET / 2 + Global::TRUCK_RAIL_SIZE;

    for (int i = 0; i < truckCount; ++i) {
        float posY;
        float posX;

        posX = Global::WINDOW_WIDTH - (rand() % Global::WINDOW_WIDTH);
        posY = truckSpawnPosition + Global::TRUCK_RAIL_SIZE * i;

        int truckIndex = rand() % Global::TRUCKS.size();
        const Global::TruckData& truckData = Global::TRUCKS[truckIndex];
        // Use the currentCheckpoint to add to the trucks base speed, so the random is applied to de speed
        float speed = Global::TRUCK_BASE_SPEED + (currentCheckpoint * 1.3) + static_cast<float>(rand() % Global::TRUCK_SPEED_RANGE) / 10.0f;
        bool flipMovement = rand() % 2;
        trucks.emplace_back(posX, posY, speed, flipMovement, Global::TRUCKS[truckIndex].textureSize, Global::TRUCKS[truckIndex].rect, Global::TRUCKS[truckIndex].truckSize);
    }

    return trucks;
}

TileMap LevelGenerator::GenerateTileMap(float checkpointY, int currentCheckpoint) {
    TileMap tileMap;
    std::string tilesetPath = Global::TILEMAP_SPRITE_PATH;

    //Desired tile size
    sf::Vector2u tileSize(70, 70);

    // Calculates de tile size
    int width = windowSize.x / tileSize.x;
    int height = Global::CHECKPOINT_DISTANCE / tileSize.y;

    // Covers the hole area
    if (windowSize.x % tileSize.x != 0) width += 1;
    if ((int)Global::CHECKPOINT_DISTANCE % tileSize.y != 0) height += 1;
    float positionY = checkpointY - Global::CHECKPOINT_DISTANCE;

    if (tileMap.load(tilesetPath, tileSize, width, height)) {
        tileMap.setPosition(0, positionY);
    }

    return tileMap;
}