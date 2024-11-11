#include "PauseMenu.h"

PauseMenu::PauseMenu(const sf::Vector2u& windowSize) : selectedItemIndex(0) {
    font.loadFromFile(Global::FONT_PATH);
    title.setFont(font);
    title.setString("Pausa");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(windowSize.x / 2 - title.getGlobalBounds().width / 2, 100);

    std::vector<std::string> options = { Global::PAUSE_OPTION_EXIT, Global::PAUSE_OPTION_RESUME };
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(30);
        item.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        item.setPosition(windowSize.x / 2 - item.getGlobalBounds().width / 2, 200 + i * 50);
        menuItems.push_back(item);
    }
}

void PauseMenu::Draw(sf::RenderWindow& window) {
    window.draw(title);
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        window.draw(menuItems[i]);
    }
}

void PauseMenu::MoveUp() {
    if (selectedItemIndex > 0) selectedItemIndex--;
}

void PauseMenu::MoveDown() {
    if (selectedItemIndex < menuItems.size() - 1) selectedItemIndex++;
}
