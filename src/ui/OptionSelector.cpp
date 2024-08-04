#include "OptionSelector.h"
#include "ResourceManager.h"
#include "Globals.h"

OptionSelector::OptionSelector() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    testOption = sf::Text("< Fullscreen >", font, FONT_SIZE_72);
    testOption.setFillColor(sf::Color::White);

    // Position title text
    testOption.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (testOption.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (testOption.getGlobalBounds().height / 2))
    );

    // Active menu option
    activeMenuOption = 0;

    // Initialize vector values
    options.push_back("Fullscreen");
    options.push_back("Windowed");
    options.push_back("Windowed Borderless");

    // Initialize cooldown for navigation
    optionSelectorCooldown = sf::milliseconds(200);
}

OptionSelector::~OptionSelector() {

}

void OptionSelector::Draw(sf::RenderWindow &win) {
    win.draw(testOption);
}

void OptionSelector::Update() {
    testOption.setString("< " + options[activeMenuOption] + " >");
    testOption.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (testOption.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (testOption.getGlobalBounds().height / 2))
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

            if (joypadX > 10.0f) {
                if (activeMenuOption == (options.size() - 1)) {
                    activeMenuOption = 0;
                } else {
                    activeMenuOption += 1;
                }
                optionSelectorClock.restart();

            } else if (joypadX < -10.0f) {
                
                if (activeMenuOption == 0) {
                    activeMenuOption = (options.size() - 1);
                } else {
                    activeMenuOption -= 1;
                }
                optionSelectorClock.restart();
            }
            
        } else {

            // Check if right or left are pressed on the keyboard
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

                // Navigate options
                activeMenuOption += 1;
                if ((options.size() - 1) == activeMenuOption) {
                    activeMenuOption = 0;
                }

                // Restart clock for navigation cooldown
                optionSelectorClock.restart();

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

                if (activeMenuOption == 0) {
                    activeMenuOption = (options.size() - 1);
                } else {
                    activeMenuOption -= 1;
                }

                optionSelectorClock.restart();
            }
        }
    }
}
