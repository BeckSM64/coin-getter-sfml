#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Screen.h"
#include "OptionSelector.h"

class ScreenStyleOptionSelector : public OptionSelector {

    private:
        void GetUserInput() override;

    public:
        ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap);
        ~ScreenStyleOptionSelector() override;
        void Draw(sf::RenderWindow &win) override;
};
