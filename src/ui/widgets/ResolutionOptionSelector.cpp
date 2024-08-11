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

    // Set enabled
    isEnabled = true;

    // Set the active menu option based on settings file
    activeMenuOption = settingsManager.GetIndexOfResolutionMap(settingsManager.GetResolution());
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

        // Check if selector should be disabled
        // In this case, only disable if current
        // applied display mode is set to full screen
        // if (displayMode == sf::Style::Fullscreen) {
        //     SetEnabled(false);
        // }
    }
}
