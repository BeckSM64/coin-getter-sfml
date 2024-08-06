#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class OptionSelector {

    public:
        OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, float positionX, float positionY);
        virtual ~OptionSelector() = default;
        virtual void Draw(sf::RenderWindow &win) = 0;
        void Update();
        void GetUserInput();

    protected:
        OptionSelector() = default;
        sf::Text optionText;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        int activeMenuOption;
        std::map<int, std::string> optionsIdToOptionsStringMap;
        bool optionSelected; // Flag to determine if option was selected
};
