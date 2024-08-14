#include <map>
#include "VolumeOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

VolumeOptionSelector::~VolumeOptionSelector() {

}

VolumeOptionSelector::VolumeOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position)
    : OptionSelector(optionsIdToOptionsStringMap, position) {

    // Set if this option selector is active
    isActive = false;

    // Set enabled
    isEnabled = true;
}

void VolumeOptionSelector::ApplySetting(sf::RenderWindow &win) {


    // Check if option to update screen style was selected
    if (optionSelected && isEnabled) {

        optionSelected = false; // Reset flag
    }
}
