#pragma once
#include <memory>
#include <stack>
#include "MainMenuScreen.h"
#include "MainGameScreen.h"
#include "Globals.h"
#include "Screen.h"

class Game {

    private:
        sf::RenderWindow win;
        sf::View view;
        std::shared_ptr<CoinGetter::Screen> currentScreen; // Pointer to the current screen
        sf::Color backgroundColor;
        sf::Clock stateTransitionClock;
        sf::Time stateTransitionCooldown;
        bool isScreenTransitioning;
        std::stack<std::shared_ptr<CoinGetter::Screen>> screenStack;

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
