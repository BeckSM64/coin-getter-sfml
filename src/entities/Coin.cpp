#include <SFML/Graphics.hpp>
#include <cmath> // For std::cos, std::sin, and std::sqrt
#include "Coin.h"
#include "Globals.h"
#include "ResourceManager.h"

// Constructor
Coin::Coin() {

    // Load texture and set up sprite
    sprite.setTexture(ResourceManager::GetInstance().GetTexture("coin"));

    // Initialize position and velocity
    const sf::VideoMode& desktopMode = sf::VideoMode::getDesktopMode();
    sprite.setPosition(
        getRandomNumber(0, desktopMode.width - sprite.getGlobalBounds().width),
        getRandomNumber(0, desktopMode.height - sprite.getGlobalBounds().height)
    );

    float speed = getRandomFloat(5.0f, 10.0f);
    float angle = getRandomFloat(0.0f, 2 * 3.14159f);

    vel.x = speed * std::cos(angle);
    vel.y = speed * std::sin(angle);

    sprite.setScale(0.5f, 0.5f);
}

// Update method
void Coin::Update() {

    // Move the coin
    sprite.move(vel);

    // Handle bouncing off the edges
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.left < 0 || bounds.left + bounds.width > sf::VideoMode::getDesktopMode().width) {
        vel.x = -vel.x;
    }

    if (bounds.top < 0 || bounds.top + bounds.height > sf::VideoMode::getDesktopMode().height) {
        vel.y = -vel.y;
    }
}