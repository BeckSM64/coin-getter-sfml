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
    if (optionSelected && isEnabled) {

        // Get display mode from settings file
        sf::Uint32 displayMode = settingsManager.GetDisplayMode();

        // Get the resolution from the settings manager
        sf::Vector2f screenResolution = settingsManager.GetResolutionFromString(optionsIdToOptionsStringMap[activeMenuOption]);

        // Overwrite settings file
        settingsManager.SetResolution(screenResolution);

        // Get the resolution after setting it, this is weird, but it's to ensure we're getting a valid resolution
        screenResolution = settingsManager.GetResolution();

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        win.create(
            sf::VideoMode(screenResolution.x, screenResolution.y),
            "[COIN GETTER]",
            displayMode
        );
        win.setFramerateLimit(60);

        // Set window and taskbar icon
        sf::Image &icon = ResourceManager::GetInstance().GetIcon("coinGetterIcon");
        win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        optionSelected = false; // Reset flag
    }
}

void ResolutionOptionSelector::UpdateEnabled() {

    // Check if selector should be disabled
    // In this case, only disable if current
    // applied display mode is set to full screen
    if (settingsManager.GetDisplayMode() == sf::Style::Fullscreen) {
        SetEnabled(false);
    } else {
        SetEnabled(true);
    }
}
