#include <map>
#include "ResolutionOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

ResolutionOptionSelector::~ResolutionOptionSelector() {

}

ResolutionOptionSelector::ResolutionOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position)
    : OptionSelector(optionsIdToOptionsStringMap, position) {

    // Set if this option selector is active
    isActive = false;
}

void ResolutionOptionSelector::ApplySetting(sf::RenderWindow &win) {

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
