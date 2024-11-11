#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"

class GameOverScreen {
public:
    GameOverScreen(const sf::Vector2u& windowSize);
    void Draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() const { return selectedItemIndex; }

private:
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;
    sf::Font font;
    sf::Text title;
};
