#pragma once
#include <vector>
#include "Coin.h"

class CoinManager {

    private:
        std::vector<Coin> coinCollection;

    public:
        CoinManager();
        ~CoinManager();
        void Update();
        void Draw(sf::RenderWindow &win);
        std::vector<Coin>& GetCollection();
        void RefillCollection();
};