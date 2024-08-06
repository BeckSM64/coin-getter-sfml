#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"

class ScreenStyleOptionSelector : public OptionSelector {

    public:
        ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        ~ScreenStyleOptionSelector() override;
        void Draw(sf::RenderWindow &win) override;
};
