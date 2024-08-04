#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class OptionSelector {

    private:
        sf::Text testOption;
        sf::Text testOption1;
        sf::Text testOption2;
        std::vector<std::string> options;
        int activeMenuOption;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        void GetUserInput();

    public:
        OptionSelector();
        ~OptionSelector();
        void Draw(sf::RenderWindow &win);
        void Update();
};