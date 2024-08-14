#pragma once
#include "MenuButton.h"
#include "Globals.h"

class MainMenuButton : public MenuButton {

    public:
        MainMenuButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState);
        ~MainMenuButton();

    private:
        void ApplySetting() override;
};
