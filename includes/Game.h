#pragma once
#include <memory>
#include "MainMenuScreen.h"
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
        void Draw();
        void HandleEvents();
        void ManageGameState();
        GameState currentGameState;
};
