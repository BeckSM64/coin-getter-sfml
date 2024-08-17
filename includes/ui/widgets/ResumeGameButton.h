#pragma once
#include "MenuButton.h"
#include "Globals.h"

class ResumeGameButton : public MenuButton {

    public:
        ResumeGameButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState);
        ~ResumeGameButton();

    private:
        void ApplySetting() override;
};
