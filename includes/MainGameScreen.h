#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CoinManager.h"
#include "Screen.h"

class MainGameScreen : public CoinGetter::Screen {

    private:
        Player *player;
        CoinManager *coinManager;
        bool isPaused;
        bool wasStartPressed;
        sf::Text pauseText;
        GameState currentGameState;
        void GetUserInput();

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        GameState GetGameState();
};
