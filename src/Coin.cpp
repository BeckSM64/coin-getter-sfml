#include <SFML/Graphics.hpp>
#include "Coin.h"
#include "Globals.h"

Coin::Coin() {

    // Load texture for coin sprite
    coinTexture.loadFromFile("sprites/coin.png");

    // Create coin sprite
    coinSprite.setTexture(coinTexture);

    // Coin position
    pos.x = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().width - coinSprite.getGlobalBounds().width);
    pos.y = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().height - coinSprite.getGlobalBounds().height);

    // Coin velocity
    vel.x = vel.y = (float) getRandomFloat(-10.0f, 10.0f);

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
