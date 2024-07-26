#pragma once
#include "MainMenu.h"
#include "MainGameScreen.h"
#include "Globals.h"

class Game {


    private:
        sf::RenderWindow win;
        MainMenu *mainMenu = nullptr;
        MainGameScreen *mainGameScreen = nullptr;

    public:
        Game();
        ~Game();
        void Run();
        void Update();
        GameState currentGameState;
};
