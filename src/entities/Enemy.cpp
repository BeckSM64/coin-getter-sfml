#include <SFML/Graphics.hpp>
#include <cmath> // For std::cos, std::sin
#include "Enemy.h"
#include "ResourceManager.h"

// Constructor
Enemy::Enemy() {
    // Get ResourceManager instance
    ResourceManager& resourceManager = ResourceManager::GetInstance();

    // Load texture and set up sprite
    sprite.setTexture(resourceManager.GetTexture("enemy"));

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = resourceManager.GetScreenResolution();

    // Initialize position and velocity
    sprite.setPosition(
        resourceManager.GetRandomNumber(0, screenResolution.x - sprite.getGlobalBounds().width),
        resourceManager.GetRandomNumber(0, screenResolution.y - sprite.getGlobalBounds().height)
    );

    // Get scale factor from ResourceManager
    float scaleFactor = resourceManager.GetScaleFactor();

    // Initialize speed and angle, applying scale factor to speed
    float speed = resourceManager.GetRandomFloat(5.0f, 10.0f) * scaleFactor;
    float angle = resourceManager.GetRandomFloat(0.0f, 2 * 3.14159f);

    // Set velocity with scale factor applied
    vel.x = speed * std::cos(angle);
    vel.y = speed * std::sin(angle);

    // Set scale for sprite
    sprite.setScale(scaleFactor / 2, scaleFactor / 2);
}

// Update method
void Enemy::Update() {
    // Move the enemy
    sprite.move(vel);

    // Get screen resolution from ResourceManager
    ResourceManager& resourceManager = ResourceManager::GetInstance();
    sf::Vector2u screenResolution = resourceManager.GetScreenResolution();

    // Handle bouncing off the edges
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.left < 0 || bounds.left + bounds.width > screenResolution.x) {
        vel.x = -vel.x;
    }

    if (bounds.top < 0 || bounds.top + bounds.height > screenResolution.y) {
        vel.y = -vel.y;
    }

    // Update hitbox
    hitBox = sprite.getGlobalBounds();
}
