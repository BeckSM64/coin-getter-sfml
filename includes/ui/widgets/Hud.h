#pragma once
#include <SFML/Graphics.hpp>
#include "HealthBar.h"
#include "CoinCounter.h"

class Hud {

    private:
        HealthBar healthBar;
        CoinCounter coinCounter;

    public:
        Hud();
        ~Hud();
        void Draw(sf::RenderWindow &win);
        void Update(int playerHealth, int coinCount);
};
