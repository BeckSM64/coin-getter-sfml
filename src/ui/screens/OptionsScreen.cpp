#include <memory>
#include "OptionsScreen.h"
#include "ResourceManager.h"
#include "ScreenStyleOptionSelector.h"
#include "ResolutionOptionSelector.h"
#include "MainMenuButton.h"
#include "Globals.h"
#include "SettingsManager.h"

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

    // Initialize settings
    SettingsManager::GetInstance().InitializeSettings();

    // Setup option menu selectors
    std::map<int, std::string> videoOptionIdToOptionStringMap = SettingsManager::GetInstance().GetValidDisplayModesMap();
    videoOptionSelector = std::make_unique<ScreenStyleOptionSelector>(videoOptionIdToOptionStringMap, sf::Vector2f(0, 100 * scaleFactor));

    std::map<int, std::string> resolutionOptionIdToOptionStringMap = SettingsManager::GetInstance().GetValidResolutionMap();
    resolutionOptionSelector = std::make_unique<ResolutionOptionSelector>(resolutionOptionIdToOptionStringMap, sf::Vector2f(0, 200 * scaleFactor));

    // Setup menu buttons
    mainMenuButton = std::make_unique<MainMenuButton>("MAIN MENU", sf::Vector2f(0, 300 * scaleFactor), currentGameState);

    // Add menu options to vector of menu otpions
    menuOptions.push_back(std::move(videoOptionSelector));
    menuOptions.push_back(std::move(resolutionOptionSelector));
    menuOptions.push_back(std::move(mainMenuButton));

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

            if (joypadY < -10.0f) {
                
                // Navigate selector options
                menuOptions[activeMenuOptionIndex]->SetActive(false);
                if (activeMenuOptionIndex == 0) {
                    activeMenuOptionIndex = menuOptions.size() - 1;
                } else {
                    activeMenuOptionIndex -= 1;
                }
                menuOptions[activeMenuOptionIndex]->SetActive(true);
                menuOptionsClock.restart();

            } else if (joypadY > 10.0f) {
                
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

                menuOptions[activeMenuOptionIndex]->SetActive(false);
                if (activeMenuOptionIndex == 0) {
                    activeMenuOptionIndex = menuOptions.size() - 1;
                } else {
                    activeMenuOptionIndex -= 1;
                }
                menuOptions[activeMenuOptionIndex]->SetActive(true);
                menuOptionsClock.restart();

            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

                menuOptions[activeMenuOptionIndex]->SetActive(false);
                if (activeMenuOptionIndex == menuOptions.size() - 1) {
                    activeMenuOptionIndex = 0;
                } else {
                    activeMenuOptionIndex += 1;
                }
                menuOptions[activeMenuOptionIndex]->SetActive(true);
                menuOptionsClock.restart();
            }
        }
    }
}

GameState OptionsScreen::GetGameState() {
    return currentGameState;
}
