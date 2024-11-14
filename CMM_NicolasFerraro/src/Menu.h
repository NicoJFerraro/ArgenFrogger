#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Menu {
public:
    Menu(const sf::Vector2u& windowSize);
    void Draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() const { return selectedItemIndex; }
    
private:
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;
    sf::Font font;
    sf::Text title;
    sf::Texture backgroundMenu;
    sf::Sprite backgroundSprite;
};
