#pragma once
#include <memory>
#include "MainMenu.h"
#include "MainGameScreen.h"
#include "Globals.h"
#include "Screen.h"

class Game {

    private:
        sf::RenderWindow win;
        std::shared_ptr<CoinGetter::Screen> currentScreen; // Pointer to the current screen
        sf::Color backgroundColor;

    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Draw(sf::RenderWindow &win);
        void HandleEvents();
        GameState currentGameState;
};
