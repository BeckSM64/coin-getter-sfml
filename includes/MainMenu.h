#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Globals.h"
#include "CoinManager.h"
#include "Screen.h"

class MainMenu : public CoinGetter::Screen {

    private:
        sf::Text titleText;
        sf::Sprite playerSprite;
        int timer;
        int navigationTimer;
        sf::Text startGameOption;
        sf::Text highScoresOption;
        sf::Text controlsOption;
        sf::Text optionsOption;
        sf::Text quitOption;
        std::vector<sf::Text> menuOptions;
        GameState currentGameState;
        enum menuOptionsEnum {
            START,
            HIGHSCORES,
            CONTROLS,
            OPTIONS,
            QUIT
        };
        int currentMenuOption;
        CoinManager *coinManager;
        bool wasStartPressed;
        sf::Clock keyPressClock;
        const sf::Time keyPressCooldown = sf::milliseconds(200); // 200 ms cooldown
        sf::Sound backgroundMusic;
        void ChangeTitleColor();
        void DrawPlayerImage(sf::RenderWindow &win);
        void DrawMenuOptions(sf::RenderWindow &win);
        void GetUserInput();

    public:
        MainMenu();
        ~MainMenu();
        void Run();
        void Update();
        void Draw(sf::RenderWindow &win);
        GameState GetGameState();
};
