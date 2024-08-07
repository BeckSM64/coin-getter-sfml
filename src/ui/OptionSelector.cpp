#include <map>
#include "OptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

OptionSelector::OptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap, sf::Vector2f position) {

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
    optionText.setPosition(position);

    // Active menu option
    activeMenuOption = 0;

    // Setup options map
    this->optionsIdToOptionsStringMap = optionsIdToOptionsStringMap;

    // Initialize cooldown for navigation
    optionSelectorCooldown = sf::milliseconds(200);

    // Don't update screen style
    optionSelected = false;

    // Set position
    this->position = position;
}

void OptionSelector::Update() {

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();
    
    optionText.setString("< " + optionsIdToOptionsStringMap[activeMenuOption] + " >");
    optionText.setPosition(
        (screenResolution.x / 2 - (optionText.getGlobalBounds().width / 2)),
        position.y
    );
    GetUserInput();
}

void OptionSelector::GetUserInput() {

    // Check if cooldown for navigation has been reached
    if (optionSelectorClock.getElapsedTime() > optionSelectorCooldown) {

        float joypadX = 0.0f;

        // Check if joystick 0 is connected
        if (sf::Joystick::isConnected(0)) {

            joypadX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

            // Navigate selector options
            if (joypadX > 10.0f) {
                if (activeMenuOption == (optionsIdToOptionsStringMap.size() - 1)) {
                    activeMenuOption = 0;
                } else {
                    activeMenuOption += 1;
                }

                optionSelectorClock.restart();

            } else if (joypadX < -10.0f) {
                
                if (activeMenuOption == 0) {
                    activeMenuOption = (optionsIdToOptionsStringMap.size() - 1);
                } else {
                    activeMenuOption -= 1;
                }

                optionSelectorClock.restart();
            }

            // Check if option is selected
            if (sf::Joystick::isButtonPressed(0, 2)) {

                optionSelected = true; // Set flag to update screen style to true
            }
            
        } else {

            // Check if right or left are pressed on the keyboard
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

                // Navigate options
                if (activeMenuOption == (optionsIdToOptionsStringMap.size() - 1)) {
                    activeMenuOption = 0;
                } else {
                    activeMenuOption += 1;
                }

                optionSelectorClock.restart();

                // Restart clock for navigation cooldown
                optionSelectorClock.restart();

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

                if (activeMenuOption == 0) {
                    activeMenuOption = (optionsIdToOptionsStringMap.size() - 1);
                } else {
                    activeMenuOption -= 1;
                }

                optionSelectorClock.restart();
            }
        }
    }
}
