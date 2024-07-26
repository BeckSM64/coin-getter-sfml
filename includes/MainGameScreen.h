#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CoinManager.h"

class MainGameScreen {

    private:
        Player *player;
        CoinManager *coinManager;
        bool isPaused;
        bool wasStartPressed;
        sf::Font font;
        sf::Text pauseText;
        void GetUserInput();

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
};
