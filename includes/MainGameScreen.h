#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "CoinManager.h"
#include "Screen.h"
#include "Entity.h"

class MainGameScreen : public CoinGetter::Screen {

    private:
        Entity *player;
        CoinManager *coinManager;
        bool isPaused;
        bool wasStartPressed;
        sf::Text pauseText;
        GameState currentGameState;
        sf::Sound backgroundMusic;
        void GetUserInput();

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        GameState GetGameState();
};
