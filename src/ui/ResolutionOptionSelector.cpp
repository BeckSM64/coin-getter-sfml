#include <map>
#include "ResolutionOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

ResolutionOptionSelector::~ResolutionOptionSelector() {

}

ResolutionOptionSelector::ResolutionOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, float positionX, float positionY)
    : OptionSelector(optionsIdToOptionsStringMap, positionX, positionY) {

}

void ResolutionOptionSelector::Draw(sf::RenderWindow &win) {

    // Draw active option text
    win.draw(optionText);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Check if option to update screen style was selected
    if (optionSelected) {

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        if (optionsIdToOptionsStringMap[activeMenuOption] == "1920x1080") {

            win.create(sf::VideoMode(1920, 1080), "[COIN GETTER]", sf::Style::None);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "1600x900") {

            win.create(sf::VideoMode(1600, 900), "[COIN GETTER]", sf::Style::None);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "1280x720") {

            win.create(sf::VideoMode(1280, 720), "[COIN GETTER]", sf::Style::None);
        }
        optionSelected = false; // Reset flag
    }
}
