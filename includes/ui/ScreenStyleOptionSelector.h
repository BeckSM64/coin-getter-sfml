#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"

class ScreenStyleOptionSelector : public OptionSelector {

    public:
        ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, float positionX, float positionY);
        ~ScreenStyleOptionSelector() override;
        void Draw(sf::RenderWindow &win) override;
};
