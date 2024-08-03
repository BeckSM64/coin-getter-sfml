#include <SFML/Graphics.hpp>
#include "Hud.h"

Hud::Hud() {

}

Hud::~Hud() {

}

void Hud::Draw(sf::RenderWindow &win) {
    healthBar.Draw(win);
}

void Hud::Update(int playerHealth) {
    healthBar.Update(playerHealth);
}
