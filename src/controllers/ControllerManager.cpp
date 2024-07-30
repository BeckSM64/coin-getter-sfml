#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "ControllerManager.h"
#include "ResourceManager.h"

// Function to check if a button state is pressed or not
std::string ControllerManager::GetButtonState(bool isPressed) {
    return isPressed ? "Pressed" : "Released";
}

std::vector<sf::Text> ControllerManager::GetJoystickButtons(unsigned int joystickIndex) {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    std::vector<sf::Text> buttonStateTextArray;

    // Get the number of buttons on the joystick
    unsigned int buttonCount = sf::Joystick::getButtonCount(joystickIndex);
    std::cout << "Joystick " << joystickIndex << " Button Count: " << buttonCount << std::endl;

    // Print button states
    for (unsigned int i = 0; i < buttonCount; ++i) {
        bool isPressed = sf::Joystick::isButtonPressed(joystickIndex, i);
        std::cout << "Button " << i << ": " << GetButtonState(isPressed) << std::endl;
        std::string buttonStateString = "Button " + std::to_string(i) + ": " + GetButtonState(isPressed);
        sf::Text buttonStateText = sf::Text(buttonStateString, font);
        buttonStateTextArray.push_back(buttonStateText);
    }

    return buttonStateTextArray;
}
