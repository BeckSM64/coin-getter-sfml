#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"
#include "ResourceManager.h"
#include "Enemy.h"

MainGameScreen::MainGameScreen() {

    player = std::make_unique<Player>();
    coinManager = new CoinManager();
    enemyManager = new EnemyManager();
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
}

MainGameScreen::~MainGameScreen() {

    delete(coinManager);
    coinManager = nullptr;
}

void MainGameScreen::Draw(sf::RenderWindow &win) {
    player->Draw(win);
    coinManager->Draw(win);
    enemyManager->Draw(win);

    if (isPaused) {
        win.draw(pauseText);
    }
}

void MainGameScreen::Update() {

    // Update the game if it's not paused
    if (!isPaused) {
        player->Update();
        coinManager->Update();
        enemyManager->Update();
    }
    
    GetUserInput();
    CollisionDetection();
}

void MainGameScreen::GetUserInput() {

    bool isStartCurrentlyPressed;

    // Check if joystick 0 is connected
    if (sf::Joystick::isConnected(0)) {
        isStartCurrentlyPressed = sf::Joystick::isButtonPressed(0, 9);
    } else {
        // Check if the Enter key is released
        isStartCurrentlyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    }

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

Player * MainGameScreen::GetPlayer() {
    return dynamic_cast<Player *>(player.get());
}

GameState MainGameScreen::GetGameState() {
    return currentGameState;
}

void MainGameScreen::CollisionDetection() {

    // Reference to the coin collection
    auto& coins = coinManager->GetCollection();

    for (auto it = coins.begin(); it != coins.end(); ) {
        if (player->GetHitbox().intersects(it->GetHitbox())) {

            // Remove the coin and get the next valid iterator
            it = coins.erase(it);

            // Collect coin, add to wallet
            GetPlayer()->AddToWallet(1);
        } else {

            // Move to the next element
            ++it;
        }
    }
    std::cout << GetPlayer()->GetWalletValue() << std::endl;
}
