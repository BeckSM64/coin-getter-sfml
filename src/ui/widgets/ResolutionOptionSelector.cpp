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

        // Get display mode from settings file
        sf::Uint32 displayMode = settingsManager.GetDisplayMode();

        // Get the resolution from the settings manager
        sf::Vector2f screenResolution = settingsManager.GetResolutionFromString(optionsIdToOptionsStringMap[activeMenuOption]);

        // Overwrite settings file
        settingsManager.SetResolution(screenResolution);

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        win.create(
            sf::VideoMode(screenResolution.x, screenResolution.y),
            "[COIN GETTER]",
            displayMode
        );

        optionSelected = false; // Reset flag
    }
}