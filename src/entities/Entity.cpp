#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ResourceManager.h"

void Entity::DrawEntityImage(sf::RenderWindow &win) {
    win.draw(sprite);
}

void Entity::ConstrainToScreen() {

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Constrain x
    if (pos.x + sprite.getGlobalBounds().width >= screenResolution.x) {
        pos.x = (float) screenResolution.x - sprite.getGlobalBounds().width;
        vel.x *= -1;
    } else if (pos.x <= 0) {
        pos.x = 0.0f;
        vel.x *= -1;
    }

    // Constrain y
    if (pos.y + sprite.getGlobalBounds().height >= screenResolution.y) {
        pos.y = (float) screenResolution.y - sprite.getGlobalBounds().height;
        vel.y *= -1;
    } else if (pos.y <= 0) {
        pos.y = 0.0f;
        vel.y *= -1;
    }
}

void Entity::Draw(sf::RenderWindow &win) {
    DrawEntityImage(win);

    // TODO: TEST REMOVE THIS
    if (sf::Joystick::isConnected(0)) {
        if (sf::Joystick::isButtonPressed(0, 3)) {
            win.create(sf::VideoMode(1920, 1080), "[COIN GETTER]", sf::Style::None);
            win.setFramerateLimit(60);
        }
    }
}

sf::FloatRect Entity::GetHitbox() const {
    return hitBox;
}

sf::Vector2f Entity::GetVelocity() const {
    return vel;
}

void Entity::SetVelocity(sf::Vector2f velocity) {
    
    // Scale the velocity based on the current scale factor
    float scaleFactor = ResourceManager::GetInstance().GetScaleFactor();
    vel = velocity * scaleFactor;
}

void Entity::SetPosition(sf::Vector2f position) {
    pos = position;
}

sf::Vector2f Entity::GetPosition() const {
    return pos;
}

bool Entity::IsDamageable() const {
    return isDamageable;
}

void Entity::SetDamageable(bool damageable) {
    isDamageable = damageable;
}
