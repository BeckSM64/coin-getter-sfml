#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"

MainGameScreen::MainGameScreen() {

    player = new Player();
    coinManager = new CoinManager();
    isPaused = false;
    wasStartPressed = false;

    // Setup font
    font.loadFromFile("./fonts/RetroComputer.ttf");

    // Create title text
    pauseText = sf::Text("[PAUSE]", font, 128);
    pauseText.setFillColor(sf::Color::White);

    // Position pause text
    pauseText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (pauseText.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (pauseText.getGlobalBounds().height / 2))
    );

    currentGameState = GameState::MAIN_GAME;
}

MainGameScreen::~MainGameScreen() {

    delete(player);
    player = nullptr;

    delete(coinManager);
    coinManager = nullptr;
}

void MainGameScreen::Draw(sf::RenderWindow &win) {
    player->Draw(win);
    coinManager->Draw(win);

    if (isPaused) {
        win.draw(pauseText);
    }
}

void MainGameScreen::Update() {

    // Update the game if it's not paused
    if (!isPaused) {
        player->Update();
        coinManager->Update();
    }
    
    GetUserInput();
}

void MainGameScreen::GetUserInput() {

    // Check if the Enter key is released
    bool isStartCurrentlyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

    // Check if the start button was pressed and released
    if (!isStartCurrentlyPressed && wasStartPressed) {
        if (isPaused) {
            isPaused = false;
            std::cout << "PAUSING" << std::endl;
        } else {
            isPaused = true;
            std::cout << "UNPAUSING" << std::endl;

        }
    }

    // Update the previous state
    wasStartPressed = isStartCurrentlyPressed;
}

GameState MainGameScreen::GetGameState() {
    return currentGameState;
}
