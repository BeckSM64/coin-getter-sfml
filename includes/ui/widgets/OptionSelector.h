#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "MenuOption.h"
#include "SettingsManager.h"

class OptionSelector : public MenuOption {

    public:
        virtual ~OptionSelector() = default;

    protected:
        OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position);
        OptionSelector() = default;
        virtual void ApplySetting(sf::RenderWindow &win) = 0;
        sf::Text optionText;
        sf::Clock optionSelectorClock;
        sf::Time optionSelectorCooldown;
        int activeMenuOption;
        std::map<int, std::string> optionsIdToOptionsStringMap;
        bool optionSelected; // Flag to determine if option was selected
        sf::Vector2f position;
        SettingsManager &settingsManager = SettingsManager::GetInstance();

    private:
        void Draw(sf::RenderWindow &win);
        void Update() override;
        void GetUserInput() override;
};
