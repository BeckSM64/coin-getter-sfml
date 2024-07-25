#include "Player.h"
#include <iostream>

Player::Player() {

    if (!playerTexture.loadFromFile("sprites/player.png"))
    {
        std::cout << "DIDNT LOAD PLAYER IMAGE" << std::endl;
    } else {
        std::cout << "LOADED PLAYER IMAGE" << std::endl;
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(sf::Vector2f(1.0f, 1.0f));
    playerSprite.setPosition(100.0f, 100.0f);
}

Player::~Player() {

}

void Player::Draw(sf::RenderWindow &win) {
    DrawPlayerImage(win);
}

void Player::Update() {

}

void Player::DrawPlayerImage(sf::RenderWindow &win) {
    win.draw(playerSprite);
}
