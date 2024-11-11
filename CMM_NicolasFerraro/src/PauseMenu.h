#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "SaveManager.cpp"

class PauseMenu {
public:
    PauseMenu(const sf::Vector2u& windowSize);
    void Draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetSelectedOption() const { return selectedItemIndex; }

private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int selectedItemIndex;
};

#endif
