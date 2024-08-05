#include <map>
#include "ScreenStyleOptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

ScreenStyleOptionSelector::~ScreenStyleOptionSelector() {

}

ScreenStyleOptionSelector::ScreenStyleOptionSelector(std::map<int, std::string> &optionsIdToOptionsStringMap)
    : OptionSelector(optionsIdToOptionsStringMap) {

}

void ScreenStyleOptionSelector::Draw(sf::RenderWindow &win) {

    // Draw active option text
    win.draw(optionText);

    // Check if option to update screen style was selected
    if (optionSelected) {

        // Check which option was selected and update screen accordingly
        // Needs to be done in draw because access to sf::RenderWindow is required
        if (optionsIdToOptionsStringMap[activeMenuOption] == "Fullscreen") {

            win.create(sf::VideoMode::getDesktopMode(), "[COIN GETTER]", sf::Style::Fullscreen);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "Windowed") {

            win.create(sf::VideoMode::getDesktopMode(), "[COIN GETTER]", sf::Style::Default);

        } else if (optionsIdToOptionsStringMap[activeMenuOption] == "Windowed Borderless") {

            win.create(sf::VideoMode::getDesktopMode(), "[COIN GETTER]", sf::Style::None);
        }
        optionSelected = false; // Reset flag
    }
}

void ScreenStyleOptionSelector::GetUserInput() {

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
