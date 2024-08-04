#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class OptionSelector {

    private:
        sf::Text optionText;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        int activeMenuOption;
        std::map<int, std::string> optionsIdToOptionsStringMap;
        bool updateScreenStyle; // Flag to determine if screen style option was selected
        void GetUserInput();

    public:
        OptionSelector();
        ~OptionSelector();
        void Draw(sf::RenderWindow &win);
        void Update();
};
