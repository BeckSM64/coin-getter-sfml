#include <SFML/Graphics.hpp>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"

MainGameScreen::MainGameScreen() {

    player = new Player();
    coinManager = new CoinManager();
}

MainGameScreen::~MainGameScreen() {

    delete(player);
    player = nullptr;

    delete(coinManager);
    coinManager = nullptr;
}

void MainGameScreen::Draw(sf::RenderWindow &win) {
    player->Draw(win);
    coinManager->Draw(win);
}

void MainGameScreen::Update() {
    player->Update();
    coinManager->Update();
}
