#include <map>
#include "ScreenStyleOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

ScreenStyleOptionSelector::~ScreenStyleOptionSelector() {

}

ScreenStyleOptionSelector::ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position)
    : OptionSelector(optionsIdToOptionsStringMap, position) {

    // Set the active menu option based on settings file
    activeMenuOption = settingsManager.GetIndexOfDisplayModeMap(settingsManager.GetDisplayMode());
}

void ScreenStyleOptionSelector::ApplySetting(sf::RenderWindow &win) {

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Check if option to update screen style was selected
    if (optionSelected && isEnabled) {

        // Get resolution from settings file
        sf::Vector2f screenResolution = settingsManager.GetResolution();

        // Get display mode
        sf::Uint32 displayMode = settingsManager.GetDisplayModeFromString(optionsIdToOptionsStringMap[activeMenuOption]);

        // Overwrite settings file
        settingsManager.SetDisplayMode(displayMode);

        // Check if display mode was fullscreen
        if (displayMode == sf::Style::Fullscreen) {

            // TODO: This is a workaround for the sf::Style::Fullscreen option being complete shit
            // Force bordless with the desktop resolution because for whatever reason with varying resolutions
            // the fullscreen option breaks shit and I hate it
            displayMode = sf::Style::None;
            screenResolution = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
        }

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        win.create(
            sf::VideoMode(screenResolution.x, screenResolution.y),
            "[COIN GETTER]",
            displayMode
        );
        win.setFramerateLimit(60);

        optionSelected = false; // Reset flag
    }
}
