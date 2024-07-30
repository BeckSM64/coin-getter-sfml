#include <SFML/Graphics.hpp>
#include <cmath> // For std::cos, std::sin, and std::sqrt
#include "Enemy.h"
#include "Globals.h"
#include "ResourceManager.h"

// Constructor
Enemy::Enemy() {

    // Load texture and set up sprite
    sprite.setTexture(ResourceManager::GetInstance().GetTexture("enemy"));

    // Initialize position and velocity
    const sf::VideoMode& desktopMode = sf::VideoMode::getDesktopMode();
    sprite.setPosition(
        ResourceManager::GetInstance().GetRandomNumber(0, desktopMode.width - sprite.getGlobalBounds().width),
        ResourceManager::GetInstance().GetRandomNumber(0, desktopMode.height - sprite.getGlobalBounds().height)
    );

    float speed = ResourceManager::GetInstance().GetRandomFloat(5.0f, 10.0f);
    float angle = ResourceManager::GetInstance().GetRandomFloat(0.0f, 2 * 3.14159f);

    vel.x = speed * std::cos(angle);
    vel.y = speed * std::sin(angle);

    sprite.setScale(0.5f, 0.5f);
}

// Update method
void Enemy::Update() {

    // Move the enemy
    sprite.move(vel);

    // Handle bouncing off the edges
    sf::FloatRect bounds = sprite.getGlobalBounds();
    const sf::VideoMode& desktopMode = sf::VideoMode::getDesktopMode();

    if (bounds.left < 0 || bounds.left + bounds.width > desktopMode.width) {
        vel.x = -vel.x;
    }

    if (bounds.top < 0 || bounds.top + bounds.height > desktopMode.height) {
        vel.y = -vel.y;
    }
}
