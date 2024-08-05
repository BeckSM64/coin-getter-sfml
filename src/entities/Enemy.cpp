#include <SFML/Graphics.hpp>
#include <cmath> // For std::cos, std::sin, and std::sqrt
#include "Enemy.h"
#include "Globals.h"
#include "ResourceManager.h"

// Constructor
Enemy::Enemy() {

    // Load texture and set up sprite
    sprite.setTexture(ResourceManager::GetInstance().GetTexture("enemy"));

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Initialize position and velocity
    sprite.setPosition(
        ResourceManager::GetInstance().GetRandomNumber(0, screenResolution.x - sprite.getGlobalBounds().width),
        ResourceManager::GetInstance().GetRandomNumber(0, screenResolution.y - sprite.getGlobalBounds().height)
    );

    float speed = ResourceManager::GetInstance().GetRandomFloat(5.0f, 10.0f);
    float angle = ResourceManager::GetInstance().GetRandomFloat(0.0f, 2 * 3.14159f);

    // Set Velocity 
    vel.x = speed * std::cos(angle);
    vel.y = speed * std::sin(angle);

    // Get scale factor from ResourceManager
    float scaleFactor = ResourceManager::GetInstance().GetScaleFactor();
    sprite.setScale(scaleFactor / 2, scaleFactor / 2);
}

// Update method
void Enemy::Update() {

    // Move the enemy
    sprite.move(vel);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Handle bouncing off the edges
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.left < 0 || bounds.left + bounds.width > screenResolution.x) {
        vel.x = -vel.x;
    }

    if (bounds.top < 0 || bounds.top + bounds.height > screenResolution.y) {
        vel.y = -vel.y;
    }

    // Hitbox
    hitBox = sprite.getGlobalBounds();
}
