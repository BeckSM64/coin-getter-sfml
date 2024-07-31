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

    HandleEnemyCollision(player, enemyManager->GetCollection());

    // Update the game if it's not paused
    if (!isPaused) {

        player->Update();
        coinManager->Update();
        enemyManager->Update();
    }
    
    GetUserInput();
    CollisionDetection();

    // Check if all the coins are gone and refill if they are
    if (coinManager->GetCollection().size() == 0) {
        coinManager->RefillCollection();
    }
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
}

void MainGameScreen::HandleEnemyCollision(std::unique_ptr<Entity>& player, std::vector<Enemy>& enemies) {
    for (Enemy& enemy : enemies) {
        if (player->GetHitbox().intersects(enemy.GetHitbox())) {
            // Get positions and velocities
            auto playerPos = player->GetPosition();
            auto enemyPos = enemy.GetPosition();
            auto playerVel = player->GetVelocity();
            auto enemyVel = enemy.GetVelocity();

            // Check if moving towards each other
            bool movingTowardEachOther =
                ((playerVel.x > 0 && enemyVel.x < 0 && playerPos.x < enemyPos.x) ||
                 (playerVel.x < 0 && enemyVel.x > 0 && playerPos.x > enemyPos.x)) ||
                ((playerVel.y > 0 && enemyVel.y < 0 && playerPos.y < enemyPos.y) ||
                 (playerVel.y < 0 && enemyVel.y > 0 && playerPos.y > enemyPos.y));

            if (movingTowardEachOther || (playerVel.x == 0 && playerVel.y == 0)) {
                // Invert enemy velocity
                enemy.SetVelocity(-enemyVel);
            }

            // Calculate overlap amounts
            sf::FloatRect playerBounds = player->GetHitbox();
            sf::FloatRect enemyBounds = enemy.GetHitbox();

            float overlapX = std::min(
                playerBounds.left + playerBounds.width - enemyBounds.left,
                enemyBounds.left + enemyBounds.width - playerBounds.left
            );

            float overlapY = std::min(
                playerBounds.top + playerBounds.height - enemyBounds.top,
                enemyBounds.top + enemyBounds.height - playerBounds.top
            );

            // Resolve collision by moving objects apart
            if (overlapX < overlapY) {
                // Resolve along X-axis
                float adjustX = (playerBounds.left < enemyBounds.left) ? -overlapX : overlapX;
                player->SetPosition(player->GetPosition() + sf::Vector2f(adjustX, 0));
                enemy.SetPosition(enemy.GetPosition() - sf::Vector2f(adjustX, 0));
            } else {
                // Resolve along Y-axis
                float adjustY = (playerBounds.top < enemyBounds.top) ? -overlapY : overlapY;
                player->SetPosition(player->GetPosition() + sf::Vector2f(0, adjustY));
                enemy.SetPosition(enemy.GetPosition() - sf::Vector2f(0, adjustY));
            }
        }
    }
}
