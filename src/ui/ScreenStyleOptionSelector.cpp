#include <map>
#include "ScreenStyleOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

ScreenStyleOptionSelector::~ScreenStyleOptionSelector() {

}

ScreenStyleOptionSelector::ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position)
    : OptionSelector(optionsIdToOptionsStringMap, position) {

}

void ScreenStyleOptionSelector::Draw(sf::RenderWindow &win) {

    // Draw active option text
    win.draw(optionText);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Check if option to update screen style was selected
    if (optionSelected) {

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        if (optionsIdToOptionsStringMap[activeMenuOption] == "Fullscreen") {

            win.create(sf::VideoMode(screenResolution.x, screenResolution.y), "[COIN GETTER]", sf::Style::Fullscreen);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "Windowed") {

            win.create(sf::VideoMode(screenResolution.x, screenResolution.y), "[COIN GETTER]", sf::Style::Default);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "Windowed Borderless") {

            win.create(sf::VideoMode(screenResolution.x, screenResolution.y), "[COIN GETTER]", sf::Style::None);
        }
        optionSelected = false; // Reset flag
    }
}
