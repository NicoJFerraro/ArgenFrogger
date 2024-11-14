#include "Timer.h"
#include <sstream>

Timer::Timer(float timeLimit) : timeLimit(timeLimit), remainingTime(timeLimit) {

    clock.restart();
    gamePauseTimer = 0;
    soundPlayed = false;
}

void Timer::Update() {
    if (!pauseTime)
    {
        remainingTime = timeLimit - clock.getElapsedTime().asSeconds() + gamePauseTimer;
        if (LittleTimeLeft() && !soundPlayed)
        {
            soundPlayed = true;
            AudioManager::Instance().PlaySFX(Global::SFX_TIMELEFT);
        }
    }
}

void Timer::Restart() {
    clock.restart();
    remainingTime = timeLimit;
    soundPlayed = false;
}

bool Timer::IsTimeUp() const {
    return remainingTime <= 0;
}

bool Timer::LittleTimeLeft() {
    return remainingTime <= (timeLimit/3);
}

int Timer::GetRemainingTime() const {
    return static_cast<int>(remainingTime);
}

void Timer::PauseTimer(bool pause)
{
    pauseTime = pause;
}

void Timer::InPauseUpdate()
{
    gamePauseTimer = clock.getElapsedTime().asSeconds();
    savedTime = remainingTime;
}

void Timer::Draw(sf::RenderWindow& window, const sf::Font& font) {
    std::ostringstream timerText;
    timerText << "Tiempo: " << GetRemainingTime() << "s";

    sf::Text text(timerText.str(), font, Global::FONT_SIZE);
    text.setPosition(window.getSize().x - 200, 10);

    if (LittleTimeLeft())
        text.setFillColor(Global::LITTLE_TIMELEFT_TEXT_COLOR);
    else
        text.setFillColor(Global::HUD_TEXT_COLOR);

    window.draw(text);
}
