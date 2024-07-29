#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"
#include "ResourceManager.h"
#include "Enemy.h"

MainGameScreen::MainGameScreen() {

    player = new Player();
    coinManager = new CoinManager();
    isPaused = false;
    wasStartPressed = false;

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Create title text
    pauseText = sf::Text("[PAUSE]", font, 128);
    pauseText.setFillColor(sf::Color::White);

    // Position pause text
    pauseText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (pauseText.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (pauseText.getGlobalBounds().height / 2))
    );

    currentGameState = GameState::MAIN_GAME;

    // Play game audio
    const sf::SoundBuffer &soundBuffer = ResourceManager::GetInstance().GetSoundBuffer("endo");
    backgroundMusic.setBuffer(soundBuffer);
    backgroundMusic.play();

    // Test enemy
    enemy = new Enemy();
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
    enemy->Draw(win);

    if (isPaused) {
        win.draw(pauseText);
    }
}

void MainGameScreen::Update() {

    // Update the game if it's not paused
    if (!isPaused) {
        player->Update();
        coinManager->Update();
        enemy->Update();
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
