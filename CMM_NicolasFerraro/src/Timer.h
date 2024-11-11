#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"

class Timer {
public:
    Timer(float timeLimit);
    void Update();
    void Restart();
    bool IsTimeUp() const;
    int GetRemainingTime() const;

    void Draw(sf::RenderWindow& window, const sf::Font& font);

private:
    sf::Clock clock;
    float timeLimit;
    float remainingTime;
};
