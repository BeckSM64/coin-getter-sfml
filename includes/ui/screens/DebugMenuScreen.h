#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"

class DebugMenuScreen : public CoinGetter::Screen {

    private:
        sf::Text debugText;
        GameState currentGameState;

    public:
        DebugMenuScreen();
        ~DebugMenuScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        GameState GetGameState();
        void GetUserInput();
};
