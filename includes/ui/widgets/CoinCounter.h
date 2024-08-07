#pragma once
#include <SFML/Graphics.hpp>

class CoinCounter {

    private:
        const int TOP_OF_SCREEN_PADDING = 10;
        sf::Text coinCountText;
        int coinCount = 0;

    public:
        CoinCounter();
        ~CoinCounter();
        void Draw(sf::RenderWindow &win);
        void Update(int coinCount);
};