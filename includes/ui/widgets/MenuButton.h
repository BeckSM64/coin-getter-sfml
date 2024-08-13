#pragma once
#include "MenuOption.h"
#include "Globals.h"

class MenuButton : public MenuOption {

    public:
        virtual ~MenuButton() = default;

    protected:
        MenuButton() = default;
        MenuButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState);
        sf::Text buttonText;
        sf::Vector2f position;
        GameState &currentGameState; // Need this to be able to modify game state stored in screen class that uses button
        virtual void SelectButton() = 0;

    private:
        void Draw(sf::RenderWindow &win) override;
        void Update() override;
        void GetUserInput() override;
};