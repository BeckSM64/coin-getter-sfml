#include <SFML/Graphics.hpp>
#include "Coin.h"
#include "Globals.h"
#include "ResourceManager.h"

Coin::Coin() {

    // Load texture for coin sprite from resource manager
    const sf::Texture &coinTexture = ResourceManager::GetInstance().GetTexture("coin");

    // Create coin sprite
    sprite.setTexture(coinTexture);

    // Coin position
    pos.x = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().width - sprite.getGlobalBounds().width);
    pos.y = (float) getRandomNumber(0, sf::VideoMode::getDesktopMode().height - sprite.getGlobalBounds().height);

    // Coin velocity
    vel.x = vel.y = (float) getRandomFloat(-10.0f, 10.0f);

    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setPosition(pos.x, pos.y);
}

void Coin::Update() {
    pos.x += vel.x;
    pos.y += vel.y;
    sprite.setPosition(pos.x, pos.y);
    ConstrainToScreen();
}
