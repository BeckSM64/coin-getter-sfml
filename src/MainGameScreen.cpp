#include <SFML/Graphics.hpp>
#include "MainGameScreen.h"
#include "Player.h"

MainGameScreen::MainGameScreen() {

    player = new Player();
}

MainGameScreen::~MainGameScreen() {

    delete(player);
    player == nullptr;
}

void MainGameScreen::Draw(sf::RenderWindow &win) {
    player->Draw(win);
}

void MainGameScreen::Update() {
    player->Update();
}
