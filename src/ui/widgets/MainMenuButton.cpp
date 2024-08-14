#include "MainMenuButton.h"
#include "Globals.h"

MainMenuButton::MainMenuButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState) : MenuButton(buttonTextString, position, currentGameState) {

    // Set if this option selector is active
    isActive = false;
}

MainMenuButton::~MainMenuButton() {

}

void MainMenuButton::ApplySetting() {

    if (optionSelected && isEnabled) {
        // Set the current game state to the main menu
        currentGameState = GameState::MAIN_MENU;
    }
}
