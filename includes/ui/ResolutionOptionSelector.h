#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"

class ResolutionOptionSelector : public OptionSelector {

    public:
        ResolutionOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, float positionX, float positionY);
        ~ResolutionOptionSelector() override;
        void Draw(sf::RenderWindow &win) override;
};
