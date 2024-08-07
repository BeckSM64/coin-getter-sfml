#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "MenuOption.h"

class OptionSelector : public MenuOption {

    public:
        OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        virtual ~OptionSelector() = default;
        virtual void Draw(sf::RenderWindow &win) = 0;
        void Update() override;
        void GetUserInput() override;

    protected:
        OptionSelector() = default;
        sf::Text optionText;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        int activeMenuOption;
        std::map<int, std::string> optionsIdToOptionsStringMap;
        bool optionSelected; // Flag to determine if option was selected
        sf::Vector2f position;
};
