#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "OptionSelector.h"

class OptionsScreen : public CoinGetter::Screen {

    private:
        sf::Text optionsSreenTitleText;
        GameState currentGameState;
        OptionSelector videoOptionSelector;

    public:
        OptionsScreen();
        ~OptionsScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        void GetUserInput();
        GameState GetGameState();
};
