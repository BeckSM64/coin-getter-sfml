#include "CoinManager.h"
#include "Globals.h"

CoinManager::CoinManager() {

    for (int i = 0; i < getRandomNumber(5, 20); i++) {
        coinCollection.push_back(new Coin());
    }
}

CoinManager::~CoinManager() {

    for (Coin *coin : coinCollection) {
        delete(coin);
        coin = nullptr;
    }
}

void CoinManager::Update() {

    for (Coin *coin : coinCollection) {
        coin->Update();
    }
}

void CoinManager::Draw(sf::RenderWindow &win) {

    for (Coin *coin : coinCollection) {
        coin->Draw(win);
    }
}
