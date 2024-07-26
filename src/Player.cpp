#include "Player.h"
#include "Globals.h"
#include <iostream>

Player::Player() {

    // Load texture for player sprite
    if (!playerTexture.loadFromFile("sprites/player.png"))
    {
        std::cout << "DIDNT LOAD PLAYER IMAGE" << std::endl;
    } else {
        std::cout << "LOADED PLAYER IMAGE" << std::endl;
    }

    // Player position
    pos.x = 100.0f;
    pos.y = 100.0f;

    // Player velocity
    vel.x = 0.0f;
    vel.y = 0.0f;

    // Create player sprite
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    playerSprite.setPosition(pos.x, pos.y);
}

Player::~Player() {

}

void Player::Draw(sf::RenderWindow &win) {
    DrawPlayerImage(win);
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
    playerSprite.setPosition(pos.x, pos.y);
}

void Player::DrawPlayerImage(sf::RenderWindow &win) {
    win.draw(playerSprite);
}
