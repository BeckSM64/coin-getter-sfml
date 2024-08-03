#pragma once
#include <SFML/Graphics.hpp>
#include "HealthBar.h"

class Hud {

    private:
        HealthBar healthBar;

    public:
        Hud();
        ~Hud();
        void Draw(sf::RenderWindow &win);
        void Update(int playerHealth);
};
