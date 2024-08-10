#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"
#include "ResourceManager.h"
#include "Enemy.h"
#include "Hud.h"

MainGameScreen::MainGameScreen() {

    player = std::make_unique<Player>();
    coinManager = new CoinManager();
    enemyManager = new EnemyManager();
    isPaused = false;
    wasStartPressed = false;

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_128);

    // Create title text
    pauseText = sf::Text("[PAUSE]", font, scaledFontSize);
    pauseText.setFillColor(sf::Color::White);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Position pause text
    pauseText.setPosition(
        (screenResolution.x / 2 - (pauseText.getGlobalBounds().width / 2)),
        (screenResolution.y / 2 - (pauseText.getGlobalBounds().height / 2))
    );

    currentGameState = GameState::MAIN_GAME;

    // Play game audio
    const sf::SoundBuffer &soundBuffer = ResourceManager::GetInstance().GetSoundBuffer("endo");
    backgroundMusic.setBuffer(soundBuffer);
    backgroundMusic.play();
    backgroundMusic.setLoop(true);
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

    hud.Draw(win);
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
    HandleEnemyCollision();

    // Check if all the coins are gone and refill if they are
    if (coinManager->GetCollection().size() == 0) {
        coinManager->RefillCollection();
    }

    // If player died
    if (GetPlayer()->GetHealth() == 0) {
        currentGameState = GameState::MAIN_MENU;
    }

    // Update the hud
    hud.Update(GetPlayer()->GetHealth(), GetPlayer()->GetWalletValue());
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
        } else {
            isPaused = true;
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
}

void MainGameScreen::HandleEnemyCollision() {

    for (Enemy& enemy : enemyManager->GetCollection()) {
        if (player->GetHitbox().intersects(enemy.GetHitbox()) && player->IsDamageable()) {

            GetPlayer()->SetHealth(GetPlayer()->GetHealth() - 1);
            player->SetDamageable(false);
            invinsibilityClock.restart();
        }
    }
        
    if (invinsibilityClock.getElapsedTime() >= invinsibilityCooldown) {
        player->SetDamageable(true);
    }
}