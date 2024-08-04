#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class OptionSelector {

    public:
        OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap);
        virtual ~OptionSelector() = default;
        virtual void Draw(sf::RenderWindow &win) = 0;
        void Update();

    protected:
        OptionSelector() = default;
        virtual void GetUserInput() = 0;
        sf::Text optionText;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        int activeMenuOption;
        std::map<int, std::string> optionsIdToOptionsStringMap;
        bool optionSelected; // Flag to determine if option was selected
};
