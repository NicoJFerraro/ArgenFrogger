#include "GameOverScreen.h"
#include <iostream>

GameOverScreen::GameOverScreen(const sf::Vector2u& windowSize) : selectedItemIndex(0) {
    if (!font.loadFromFile(Global::FONT_PATH)) {
        std::cerr << "Error loading " + Global::FONT_PATH << std::endl;
    }

    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(Global::TITLE_FONT_SIZE);
    title.setFillColor(Global::TITLE_COLOR);
    title.setPosition(windowSize.x / 2 - title.getGlobalBounds().width / 2, windowSize.y / 4);

    std::vector<std::string> options = {"Presiona Enter para ir Menu Principal"};
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(Global::MENU_ITEM_FONT_SIZE);
        item.setFillColor(Global::MENU_ITEM_COLOR);
        item.setPosition(windowSize.x / 2 - item.getGlobalBounds().width / 2, windowSize.y / 2 + i * Global::MENU_ITEM_SPACING);
        menuItems.push_back(item);
    }
}

void GameOverScreen::Draw(sf::RenderWindow& window) {
    window.draw(title);
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == selectedItemIndex) {
            menuItems[i].setFillColor(Global::MENU_SELECTED_COLOR);
        }
        else {
            menuItems[i].setFillColor(Global::MENU_ITEM_COLOR);
        }
        window.draw(menuItems[i]);
    }
}

void GameOverScreen::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
    }
}

void GameOverScreen::MoveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        selectedItemIndex++;
    }
}
