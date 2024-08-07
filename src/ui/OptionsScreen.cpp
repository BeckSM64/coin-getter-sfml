#include <memory>
#include "OptionsScreen.h"
#include "ResourceManager.h"
#include "ScreenStyleOptionSelector.h"
#include "ResolutionOptionSelector.h"
#include "Globals.h"

OptionsScreen::OptionsScreen() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    float scaleFactor = ResourceManager::GetInstance().GetScaleFactor();

    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_72);
    optionsSreenTitleText = sf::Text("[OPTIONS]", font, scaledFontSize);
    optionsSreenTitleText.setPosition(
        sf::Vector2f(
            (screenResolution.x / 2) - (optionsSreenTitleText.getGlobalBounds().width / 2),
            0
        )
    );

    // Set the current game state
    currentGameState = GameState::OPTIONS_MENU;

    // Setup option menu selectors
    std::map<int, std::string> videoOptionIdToOptionStringMap;
    videoOptionIdToOptionStringMap[0] = "Fullscreen";
    videoOptionIdToOptionStringMap[1] = "Windowed";
    videoOptionIdToOptionStringMap[2] = "Windowed Borderless";
    videoOptionSelector = std::make_unique<ScreenStyleOptionSelector>(videoOptionIdToOptionStringMap, sf::Vector2f(0, 100 * scaleFactor));

    std::map<int, std::string> resolutionOptionIdToOptionStringMap;
    resolutionOptionIdToOptionStringMap[0] = "1920x1080";
    resolutionOptionIdToOptionStringMap[1] = "1600x900";
    resolutionOptionIdToOptionStringMap[2] = "1280x720";
    resolutionOptionSelector = std::make_unique<ResolutionOptionSelector>(resolutionOptionIdToOptionStringMap, sf::Vector2f(0, 200 * scaleFactor));

    // Add menu options to vector of menu otpions
    menuOptions.push_back(std::move(videoOptionSelector));
    menuOptions.push_back(std::move(resolutionOptionSelector));

    // Set first element in vector as active
    menuOptions[0]->SetActive(true);

    // Set the active menu option index
    activeMenuOptionIndex = 0;

    // Initialize menu options cooldown
    menuOptionsCooldown = sf::milliseconds(200);
}

OptionsScreen::~OptionsScreen() {

}

void OptionsScreen::Draw(sf::RenderWindow & win) {
    win.draw(optionsSreenTitleText);

    for (auto &option : menuOptions) {
        option->Draw(win);
    }
}

void OptionsScreen::Update() {

    for (auto &option : menuOptions) {
        option->Update();
    }

    GetUserInput();
}

void OptionsScreen::GetUserInput() {

    // Check if cooldown for navigation has been reached
    if (menuOptionsClock.getElapsedTime() > menuOptionsCooldown) {

        float joypadY = 0.0f;

        // Check if joystick 0 is connected
        if (sf::Joystick::isConnected(0)) {

            joypadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

            if (joypadY > 10.0f) {
                
                // Navigate selector options
                menuOptions[activeMenuOptionIndex]->SetActive(false);
                if (activeMenuOptionIndex == 0) {
                    activeMenuOptionIndex = menuOptions.size() - 1;
                } else {
                    activeMenuOptionIndex -= 1;
                }
                menuOptions[activeMenuOptionIndex]->SetActive(true);
                menuOptionsClock.restart();

            } else if (joypadY < -10.0f) {
                
                menuOptions[activeMenuOptionIndex]->SetActive(false);
                if (activeMenuOptionIndex == menuOptions.size() - 1) {
                    activeMenuOptionIndex = 0;
                } else {
                    activeMenuOptionIndex += 1;
                }
                menuOptions[activeMenuOptionIndex]->SetActive(true);
                menuOptionsClock.restart();
            }
            
        } else {

            // Check if right or left are pressed on the keyboard
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

                menuOptionsClock.restart();

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

                menuOptionsClock.restart();
            }
        }
    }
}

GameState OptionsScreen::GetGameState() {
    return currentGameState;
}
