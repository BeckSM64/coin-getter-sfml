#include <SFML/Graphics.hpp>
#include "Coin.h"

Coin::Coin() {

    // Load texture for coin sprite
    coinTexture.loadFromFile("sprites/coin.png");

    // Coin position
    pos.x = 100.0f;
    pos.y = 100.0f;

    // Coin velocity
    vel.x = 0.5f;
    vel.y = 0.5f;

    // Create coin sprite
    coinSprite.setTexture(coinTexture);
    coinSprite.setScale(sf::Vector2f(0.5f, 0.5f));
    coinSprite.setPosition(pos.x, pos.y);
}

Coin::~Coin() {

}

void Coin::Update() {
    pos.x += vel.x;
    pos.y += vel.y;
    coinSprite.setPosition(pos.x, pos.y);
    ConstrainToScreen();
}

void Coin::Draw(sf::RenderWindow &win) {
    DrawCoinImage(win);
}

void Coin::DrawCoinImage(sf::RenderWindow &win) {
    win.draw(coinSprite);
}

void Coin::ConstrainToScreen() {

    // Constrain x
    if (pos.x + coinSprite.getGlobalBounds().width >= sf::VideoMode::getDesktopMode().width) {
        pos.x = (float) sf::VideoMode::getDesktopMode().width - coinSprite.getGlobalBounds().width;
        vel.x *= -1;
    } else if (pos.x <= 0) {
        pos.x = 0.0f;
        vel.x *= -1;
    }

    // Constrain y
    if (pos.y + coinSprite.getGlobalBounds().height >= sf::VideoMode::getDesktopMode().height) {
        pos.y = (float) sf::VideoMode::getDesktopMode().height - coinSprite.getGlobalBounds().height;
        vel.y *= -1;
    } else if (pos.y <= 0) {
        pos.y = 0.0f;
        vel.y *= -1;
    }
}
