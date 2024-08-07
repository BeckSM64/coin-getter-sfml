#include "HealthBar.h"
#include "ResourceManager.h"

// Constructor
HealthBar::HealthBar() {
    // Get ResourceManager instance
    ResourceManager& resourceManager = ResourceManager::GetInstance();
    float scaleFactor = resourceManager.GetScaleFactor();

    // Initialize scaled constants
    HEALTH_BAR_POSITION = sf::Vector2f(10.0f, 10.0f) * scaleFactor;
    HEALTH_BAR_SIZE = sf::Vector2f(200.0f, 50.0f) * scaleFactor;
    HEALTH_BAR_BORDER_PADDING = sf::Vector2f(5.0f, 5.0f) * scaleFactor;

    // Scale the health bar size and position
    sf::Vector2f scaledHealthBarSize = HEALTH_BAR_SIZE;
    sf::Vector2f scaledBorderPadding = HEALTH_BAR_BORDER_PADDING;
    sf::Vector2f scaledHealthBarPosition = HEALTH_BAR_POSITION;

    barBorder.setSize(scaledHealthBarSize + sf::Vector2f(scaledBorderPadding.x * 2, scaledBorderPadding.y * 2));
    barBorder.setPosition(scaledHealthBarPosition - sf::Vector2f(scaledBorderPadding.x, scaledBorderPadding.y));
    barBorder.setFillColor(sf::Color::White);

    barBackground.setSize(scaledHealthBarSize);
    barBackground.setPosition(scaledHealthBarPosition);
    barBackground.setFillColor(sf::Color::Red);

    bar.setSize(scaledHealthBarSize);
    bar.setPosition(scaledHealthBarPosition);
    bar.setFillColor(sf::Color::Green);
}

HealthBar::~HealthBar() {
}

void HealthBar::Draw(sf::RenderWindow &win) {
    // Draw health bar components
    win.draw(barBorder);
    win.draw(barBackground);
    win.draw(bar);
}

void HealthBar::Update(int playerHealth) {
    
    // Calculate the full width of the bar
    float fullWidth = HEALTH_BAR_SIZE.x;
    
    // Calculate the new width based on player health
    float healthWidth = (playerHealth / 10.0f) * fullWidth;

    // Set the size of the green bar
    bar.setSize(sf::Vector2f(healthWidth, bar.getSize().y));
}
