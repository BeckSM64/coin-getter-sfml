#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"
#include "MenuOption.h"
#include "SettingsManager.h"

class ResolutionOptionSelector : public OptionSelector {

    private:
        void ApplySetting(sf::RenderWindow &win) override;

    public:
        ResolutionOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        ~ResolutionOptionSelector() override;
};
