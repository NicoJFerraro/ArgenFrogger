#include "Menu.h"
#include <iostream>

Menu::Menu(const sf::Vector2u& windowSize) : selectedItemIndex(0) {
    if (!font.loadFromFile(Global::FONT_PATH)) {
        std::cerr << "Error loading " + Global::FONT_PATH << std::endl;
    }

    // Config title
    title.setFont(font);
    title.setString(Global::GAME_TITLE);
    title.setCharacterSize(Global::TITLE_FONT_SIZE);
    title.setFillColor(Global::TITLE_COLOR);
    title.setPosition(windowSize.x / 2 - title.getGlobalBounds().width / 2, Global::TITLE_POSITION_Y);

    // Config menu options
    std::vector<std::string> options = { Global::MENU_OPTION_PLAY, Global::MENU_OPTION_EXIT };
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(Global::MENU_ITEM_FONT_SIZE);
        item.setFillColor(Global::MENU_ITEM_COLOR);
        item.setPosition(windowSize.x / 2 - item.getGlobalBounds().width / 2, Global::MENU_ITEM_START_Y + i * Global::MENU_ITEM_SPACING);
        menuItems.push_back(item);
    }
}

void Menu::Draw(sf::RenderWindow& window) {
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

void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        selectedItemIndex++;
    }
}
