#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class MainGameScreen {

    private:
        Player *player;

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
};