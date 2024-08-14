#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"
#include "MenuOption.h"
#include "SettingsManager.h"

class VolumeOptionSelector : public OptionSelector {

    private:
        void ApplySetting(sf::RenderWindow &win) override;
        // void UpdateEnabled() override;

    public:
        VolumeOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        ~VolumeOptionSelector() override;
};
