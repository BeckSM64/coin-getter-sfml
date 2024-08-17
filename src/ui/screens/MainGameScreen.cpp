#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "MainGameScreen.h"
#include "Player.h"
#include "CoinManager.h"
#include "ResourceManager.h"
#include "Enemy.h"
#include "Hud.h"
#include "SettingsManager.h"

MainGameScreen::MainGameScreen() {

    player = std::make_unique<Player>();
    coinManager = new CoinManager();
    enemyManager = new EnemyManager();

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_128);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    currentGameState = GameState::MAIN_GAME;

    // Play game audio
    const sf::SoundBuffer &soundBuffer = ResourceManager::GetInstance().GetSoundBuffer("endo");
    backgroundMusic.setBuffer(soundBuffer);
    backgroundMusic.play();
    backgroundMusic.setLoop(true);
    int volume = SettingsManager::GetInstance().GetVolume();
    backgroundMusic.setVolume(volume); // TODO: Consider moving into abstract screen class since it seems common among screens
}

MainGameScreen::~MainGameScreen() {

    delete(coinManager);
    coinManager = nullptr;
}

void MainGameScreen::Draw(sf::RenderWindow &win) {
    player->Draw(win);
    coinManager->Draw(win);
    enemyManager->Draw(win);
    hud.Draw(win);
}

void MainGameScreen::Update() {

    player->Update();
    coinManager->Update();
    enemyManager->Update();
    
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

    // Check if joystick 0 is connected
    if (sf::Joystick::isConnected(0)) {

        // Change to the pause menu if start button is pressed
        if (sf::Joystick::isButtonPressed(0, 9)) {
            currentGameState = GameState::PAUSE_MENU;
        }
    } else {
        // Check if the Enter key is released
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            currentGameState = PAUSE_MENU;
        }
    }
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
