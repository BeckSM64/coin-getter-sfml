#include <SFML/Graphics.hpp>
#include "Entity.h"

void Entity::DrawEntityImage(sf::RenderWindow &win) {
    win.draw(sprite);
}

void Entity::ConstrainToScreen() {

    // Constrain x
    if (pos.x + sprite.getGlobalBounds().width >= sf::VideoMode::getDesktopMode().width) {
        pos.x = (float) sf::VideoMode::getDesktopMode().width - sprite.getGlobalBounds().width;
        vel.x *= -1;
    } else if (pos.x <= 0) {
        pos.x = 0.0f;
        vel.x *= -1;
    }

    // Constrain y
    if (pos.y + sprite.getGlobalBounds().height >= sf::VideoMode::getDesktopMode().height) {
        pos.y = (float) sf::VideoMode::getDesktopMode().height - sprite.getGlobalBounds().height;
        vel.y *= -1;
    } else if (pos.y <= 0) {
        pos.y = 0.0f;
        vel.y *= -1;
    }
}

void Entity::Draw(sf::RenderWindow &win) {
    DrawEntityImage(win);

    // // TODO: TEST REMOVE THIS
    // if (sf::Joystick::isConnected(0)) {
    //     if (sf::Joystick::isButtonPressed(0, 3)) {
    //         win.create(sf::VideoMode(1280, 720, 32), "[COIN GETTER]", sf::Style::None);
    //         win.setFramerateLimit(60);
    //     }
    // }
}

sf::FloatRect Entity::GetHitbox() const {
    return hitBox;
}

sf::Vector2f Entity::GetVelocity() const {
    return vel;
}

void Entity::SetVelocity(sf::Vector2f velocity) {
    vel = velocity;
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
