#include "ResumeGameButton.h"
#include "Globals.h"

ResumeGameButton::ResumeGameButton(std::string buttonTextString, sf::Vector2f position, GameState &currentGameState) : MenuButton(buttonTextString, position, currentGameState) {

    // Set if this option selector is active
    isActive = false;
}

ResumeGameButton::~ResumeGameButton() {

}

void ResumeGameButton::ApplySetting() {

    if (optionSelected && isEnabled) {
        // Set the current game state to the main game screen
        currentGameState = GameState::MAIN_GAME;
    }
}
