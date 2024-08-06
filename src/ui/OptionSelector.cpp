#include <map>
#include "OptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

OptionSelector::OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap) {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_72);
    optionText = sf::Text("< >", font, scaledFontSize);
    optionText.setFillColor(sf::Color::White);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Position title text
    optionText.setPosition(
        (screenResolution.x / 2 - (optionText.getGlobalBounds().width / 2)),
        (screenResolution.y / 2 - (optionText.getGlobalBounds().height / 2))
    );

    // Active menu option
    activeMenuOption = 0;

    // Setup options map
    this->optionsIdToOptionsStringMap = optionsIdToOptionsStringMap;

    // Initialize cooldown for navigation
    optionSelectorCooldown = sf::milliseconds(200);

    // Don't update screen style
    optionSelected = false;
}

void OptionSelector::Update() {

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();
    
    optionText.setString("< " + optionsIdToOptionsStringMap[activeMenuOption] + " >");
    optionText.setPosition(
        (screenResolution.x / 2 - (optionText.getGlobalBounds().width / 2)),
        (screenResolution.y / 2 - (optionText.getGlobalBounds().height / 2))
    );
    GetUserInput();
}
