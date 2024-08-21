#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Screen.h"
#include "OptionSelector.h"
#include "MenuButton.h"
#include "ResumeGameButton.h"

class PauseMenuScreen : public CoinGetter::Screen {

    private:
        sf::Text pauseMenuScreenTitleText;
        GameState currentGameState;
        std::unique_ptr<OptionSelector> videoOptionSelector;
        std::unique_ptr<OptionSelector> resolutionOptionSelector;
        std::unique_ptr<MenuButton> mainMenuButton;
        std::unique_ptr<ResumeGameButton> resumeGameButton;
        std::vector<std::unique_ptr<MenuOption>> menuOptions;
        sf::Clock menuOptionsClock;
        sf::Time menuOptionsCooldown;
        int activeMenuOptionIndex;

    public:
        PauseMenuScreen();
        ~PauseMenuScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        void GetUserInput();
        GameState GetGameState();
        void SetGameState(GameState gameState);
};
