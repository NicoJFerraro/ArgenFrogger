#include "TileMap.h"
#include <cstdlib>

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, int width, int height) {
    // Cargar la textura del tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // Tamaño de dibujado
    m_tileSize = tileSize;

    // Dimensiones del mapa en tiles
    m_width = width;
    m_height = height;

    // Generar el mapa aleatorio inicial
    generateRandomMap(width, height);

    // Crear el vertex array
    updateMap();

    return true;
}

void TileMap::generateRandomMap(int width, int height) {
    m_tileIndices.resize(width * height);

    // Asumiendo que el tileset tiene 4 tiles diferentes (0 a 3)
    int tileVariations = m_tileset.getSize().x / 16; // 16 es el tamaño original del tile en la textura

    for (int i = 0; i < width * height; ++i) {
        m_tileIndices[i] = rand() % tileVariations;
    }
}

void TileMap::updateMap() {
    // Redimensionar el vertex array para contener todos los quads
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_width * m_height * 4);

    // Tamaño original del tile en la textura
    sf::Vector2u textureTileSize(16, 16);

    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j) {
            // Obtener el índice del tile actual
            int tileNumber = m_tileIndices[i + j * m_width];

            // Encontrar su posición en el tileset
            int tu = tileNumber % (m_tileset.getSize().x / textureTileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / textureTileSize.x);

            // Obtener un puntero al quad actual en el vertex array
            sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

            // Definir las cuatro posiciones del quad basadas en el tamaño de dibujado
            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            // Definir las cuatro coordenadas de textura basadas en el tamaño original del tile
            quad[0].texCoords = sf::Vector2f(tu * textureTileSize.x, tv * textureTileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * textureTileSize.x, tv * textureTileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * textureTileSize.x, (tv + 1) * textureTileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * textureTileSize.x, (tv + 1) * textureTileSize.y);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Aplicar la transformación
    states.transform *= getTransform();

    // Aplicar la textura del tileset
    states.texture = &m_tileset;

    // Dibujar el vertex array
    target.draw(m_vertices, states);
}
