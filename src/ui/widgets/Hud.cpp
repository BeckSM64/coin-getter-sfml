#include <SFML/Graphics.hpp>
#include "Hud.h"

Hud::Hud() {

}

Hud::~Hud() {

}

void Hud::Draw(sf::RenderWindow &win) {
    healthBar.Draw(win);
    coinCounter.Draw(win);
}

void Hud::Update(int playerHealth, int coinCount) {
    healthBar.Update(playerHealth);
    coinCounter.Update(coinCount);
}
