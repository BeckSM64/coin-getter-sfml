#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Globals.h"
#include "ResourceManager.h"

Enemy::Enemy() {

    // Load texture for enemy sprite from resource manager
    const sf::Texture &enemyTexture = ResourceManager::GetInstance().GetTexture("enemy");

    // Create enemy sprite
    sprite.setTexture(enemyTexture);

    // Enemy position
    pos.x = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().width - sprite.getGlobalBounds().width);
    pos.y = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().height - sprite.getGlobalBounds().height);

    // Enemy velocity
    vel.x = vel.y = 8.0f;

    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setPosition(pos.x, pos.y);
}

void Enemy::Update() {
    pos.x += vel.x;
    pos.y += vel.y;
    sprite.setPosition(pos.x, pos.y);
    ConstrainToScreen();
}
