#include "TileMap.h"
#include <cstdlib>

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, int width, int height) {
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_tileSize = tileSize;

    m_width = width;
    m_height = height;

    generateRandomMap(width, height);

    updateMap();

    return true;
}

void TileMap::generateRandomMap(int width, int height) {
    m_tileIndices.resize(width * height);

    //This randomize the tiles in the tilemap, no matter how width it is
    int tileVariations = m_tileset.getSize().x / 16;

    for (int i = 0; i < width * height; ++i) {
        m_tileIndices[i] = rand() % tileVariations;
    }
}

void TileMap::updateMap() {
    // Fitt all quads in vertex array
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_width * m_height * 4);

    // Texture Tile size
    sf::Vector2u textureTileSize(16, 16);

    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j) {
            
            int tileNumber = m_tileIndices[i + j * m_width];

            // Get tileset position
            int tu = tileNumber % (m_tileset.getSize().x / textureTileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / textureTileSize.x);

            sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * textureTileSize.x, tv * textureTileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * textureTileSize.x, tv * textureTileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * textureTileSize.x, (tv + 1) * textureTileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * textureTileSize.x, (tv + 1) * textureTileSize.y);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &m_tileset;

    target.draw(m_vertices, states);
}
