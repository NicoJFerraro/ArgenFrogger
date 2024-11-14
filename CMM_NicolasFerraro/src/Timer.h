#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "AudioManager.h"

class Timer {
public:
    Timer(float timeLimit);
    void Update();
    void Restart();
    bool IsTimeUp() const;
    bool LittleTimeLeft();
    int GetRemainingTime() const;
    void PauseTimer(bool pause);
    void InPauseUpdate();

    void Draw(sf::RenderWindow& window, const sf::Font& font);

private:
    sf::Clock clock;
    float timeLimit;
    float remainingTime;
    bool pauseTime;
    float gamePauseTimer;
    float savedTime;
    bool soundPlayed;
};
