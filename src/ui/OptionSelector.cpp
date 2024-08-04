#include <map>
#include "OptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

OptionSelector::OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap) {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    optionText = sf::Text("< >", font, FONT_SIZE_72);
    optionText.setFillColor(sf::Color::White);

    // Position title text
    optionText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (optionText.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (optionText.getGlobalBounds().height / 2))
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
    optionText.setString("< " + optionsIdToOptionsStringMap[activeMenuOption] + " >");
    optionText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (optionText.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (optionText.getGlobalBounds().height / 2))
    );
    GetUserInput();
}
