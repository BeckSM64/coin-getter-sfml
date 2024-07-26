#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CoinManager.h"

class MainGameScreen {

    private:
        Player *player;
        CoinManager *coinManager;

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
};