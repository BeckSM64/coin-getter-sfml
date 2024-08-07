#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"
#include "MenuOption.h"

class ResolutionOptionSelector : public OptionSelector {

    public:
        ResolutionOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        ~ResolutionOptionSelector() override;
        void Draw(sf::RenderWindow &win) override;
};
