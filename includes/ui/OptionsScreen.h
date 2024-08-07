#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Screen.h"
#include "OptionSelector.h"

class OptionsScreen : public CoinGetter::Screen {

    private:
        sf::Text optionsSreenTitleText;
        GameState currentGameState;
        std::unique_ptr<OptionSelector> videoOptionSelector;
        std::unique_ptr<OptionSelector> resolutionOptionSelector;
        std::vector<std::unique_ptr<MenuOption>> menuOptions;

    public:
        OptionsScreen();
        ~OptionsScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        void GetUserInput();
        GameState GetGameState();
};
