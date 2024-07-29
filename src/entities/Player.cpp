#include "Player.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <iostream>

Player::Player() {

    // Get player texture from resource manager
    const sf::Texture &playerTexture = ResourceManager::GetInstance().GetTexture("player");

    // Player position
    pos.x = 100.0f;
    pos.y = 100.0f;

    // Player velocity
    vel.x = 0.0f;
    vel.y = 0.0f;

    // Create player sprite
    sprite.setTexture(playerTexture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setPosition(pos.x, pos.y);
}

void Player::Update() {

    // Check for player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        vel.y = PLAYER_MOVEMENT_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        vel.y = -PLAYER_MOVEMENT_SPEED;
    } else {
        vel.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        vel.x = - PLAYER_MOVEMENT_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        vel.x = PLAYER_MOVEMENT_SPEED;
    } else {
        vel.x = 0;
    }

    // Update player position
    pos.x += vel.x;
    pos.y += vel.y;
    sprite.setPosition(pos.x, pos.y);

    // Keep player on screen
    ConstrainToScreen();
}
