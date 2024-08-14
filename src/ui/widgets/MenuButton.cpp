#include "MenuButton.h"
#include "ResourceManager.h"
#include "Globals.h"

MenuButton::MenuButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState)
    : position(position),
      currentGameState(currentGameState) {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_72);
    buttonText = sf::Text(buttonTextString, font, scaledFontSize);
    buttonText.setFillColor(sf::Color::White);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Position title text
    buttonText.setPosition(position);

    // Option not selected by default
    optionSelected = false;
}

void MenuButton::Draw(sf::RenderWindow &win) {

    // Draw active option text
    win.draw(buttonText);

    // Set color of text
    if (isActive) {
        buttonText.setFillColor(sf::Color::Red);
    } else {
        buttonText.setFillColor(sf::Color::White);
    }
}

void MenuButton::Update() {
    
    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();
    
    // buttonText.setString("TEST");
    buttonText.setPosition(
        (screenResolution.x / 2 - (buttonText.getGlobalBounds().width / 2)),
        position.y
    );
    GetUserInput();
    ApplySetting(); // TODO: this is the right place, but should be consistent with OptionSelector's ApplySetting call
}

void MenuButton::GetUserInput() {

    // Only get user input if the menu option is being hovered over
    if (isActive && isEnabled) {

        // Check if joystick 0 is connected
        if (sf::Joystick::isConnected(0)) {

            if (sf::Joystick::isButtonPressed(0, 2)) {

                optionSelected = true;
            }
        } else {

            // Check for keyboard input if controller isn't connected
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

                optionSelected = true;
            }
        }
    }
}