#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, int width, int height);

    void generateRandomMap(int width, int height);
    void updateMap();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    // Almacenaremos los índices de los tiles
    std::vector<int> m_tileIndices;

    sf::Vector2u m_tileSize;

    sf::Texture sideWalkTexture;
    sf::Sprite sideWalkSprite;

    int m_width;
    int m_height;
};
