#include "Timer.h"
#include <sstream>

Timer::Timer(float timeLimit) : timeLimit(timeLimit), remainingTime(timeLimit) {
    clock.restart(); // Initialize clock
}

void Timer::Update() {
    remainingTime = timeLimit - clock.getElapsedTime().asSeconds();
}

void Timer::Restart() {
    clock.restart();
    remainingTime = timeLimit;
}

bool Timer::IsTimeUp() const {
    return remainingTime <= 0;
}

int Timer::GetRemainingTime() const {
    return static_cast<int>(remainingTime);
}

void Timer::Draw(sf::RenderWindow& window, const sf::Font& font) {
    std::ostringstream timerText;
    timerText << "Tiempo: " << GetRemainingTime() << "s";

    sf::Text text(timerText.str(), font, Global::FONT_SIZE);
    text.setPosition(window.getSize().x - 200, 10);
    text.setFillColor(Global::HUD_TEXT_COLOR);
    window.draw(text);
}
