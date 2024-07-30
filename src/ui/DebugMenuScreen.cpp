#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "DebugMenuScreen.h"
#include "ResourceManager.h"
#include "ControllerManager.h"

DebugMenuScreen::DebugMenuScreen() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    debugText = sf::Text("[DEBUG]", font, 72);
    debugText.setFillColor(sf::Color::White);

    // Position pause text
    debugText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (debugText.getGlobalBounds().width / 2)),
        0
    );

    currentGameState = GameState::DEBUG_MENU;
}

DebugMenuScreen::~DebugMenuScreen() {

}

void DebugMenuScreen::Draw(sf::RenderWindow &win) {

    win.draw(debugText);
    
    // Get joystick button states
    for (int i = 0; i < ControllerManager::GetInstance().GetJoystickButtons(0).size(); i++) {
        
        sf::Text text = ControllerManager::GetInstance().GetJoystickButtons(0)[i];
        text.setPosition(
            0, 25 * i
        );

        text.setFillColor(sf::Color::White);

        win.draw(text);
    }
}

void DebugMenuScreen::Update() {
    
}

void DebugMenuScreen::GetUserInput() {

}

GameState DebugMenuScreen::GetGameState() {
    return currentGameState;
}
