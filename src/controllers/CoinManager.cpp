#include "CoinManager.h"
#include "ResourceManager.h"
#include "Globals.h"

CoinManager::CoinManager() {

    for (int i = 0; i < ResourceManager::GetInstance().GetRandomNumber(5, 20); i++) {
        Coin coin;
        coinCollection.push_back(coin);
    }
}

CoinManager::~CoinManager() {

}

void CoinManager::Update() {

    for (Coin &coin : coinCollection) {
        coin.Update();
    }
}

void CoinManager::Draw(sf::RenderWindow &win) {

    for (Coin &coin : coinCollection) {
        coin.Draw(win);
    }
}

std::vector<Coin>& CoinManager::GetCollection() {
    return coinCollection;
}

void CoinManager::RefillCollection() {

    // Add more coins
    for (int i = 0; i < ResourceManager::GetInstance().GetRandomNumber(5, 20); i++) {
        Coin coin;
        coinCollection.push_back(coin);
    }
}
