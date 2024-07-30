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
}

sf::FloatRect Entity::GetHitbox() const {
    return hitBox;
}
