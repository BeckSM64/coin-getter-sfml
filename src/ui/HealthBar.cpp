#include "HealthBar.h"

HealthBar::HealthBar() {

    barBorder.setSize(HEALTH_BAR_SIZE + HEALTH_BAR_BORDER_PADDING + HEALTH_BAR_BORDER_PADDING);
    barBorder.setPosition(HEALTH_BAR_POSITION);
    barBorder.setFillColor(sf::Color::White);

    barBackground.setSize(sf::Vector2f(200.0f, 50.0f));
    barBackground.setPosition(HEALTH_BAR_POSITION + HEALTH_BAR_BORDER_PADDING);
    barBackground.setFillColor(sf::Color::Red);
    
    bar.setSize(sf::Vector2f(200.0f, 50.0f));
    bar.setPosition(HEALTH_BAR_POSITION + HEALTH_BAR_BORDER_PADDING);
    bar.setFillColor(sf::Color::Green);
    
}

HealthBar::~HealthBar() {

}

void HealthBar::Draw(sf::RenderWindow &win) {

    // Order matters for drawing
    win.draw(barBorder);
    win.draw(barBackground);
    win.draw(bar);
}

void HealthBar::Update(int playerHealth) {
    bar.setSize(sf::Vector2f((playerHealth * 10) * 2, 50.0f));
}
