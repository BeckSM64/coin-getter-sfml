#include "Player.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <iostream>

Player::Player() {

    // Get player texture from resource manager
    const sf::Texture &playerTexture = ResourceManager::GetInstance().GetTexture("player");

    // Player position
    pos.x = 100.0f;
    pos.y = 100.0f;

    // Player velocity
    vel.x = 0.0f;
    vel.y = 0.0f;

    // Create player sprite
    sprite.setTexture(playerTexture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setPosition(pos.x, pos.y);

    // Hitbox
    hitBox = sprite.getGlobalBounds();

    // Initialize wallet
    wallet = 0;
}

void Player::Update() {

    // Update hitbox
    hitBox = sprite.getGlobalBounds();

    // Variables to store the current velocity
    sf::Vector2f currentVelocity = {0.0f, 0.0f};

    // Check if joystick 0 is connected
    if (sf::Joystick::isConnected(0)) {
        float joypadX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float joypadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        // Apply deadzone to avoid drift when joystick is near center
        if (std::abs(joypadX) < DEADZONE_THRESHOLD) {
            joypadX = 0.0f;
        }
        if (std::abs(joypadY) < DEADZONE_THRESHOLD) {
            joypadY = 0.0f;
        }

        // Normalize joystick input if not zero
        float magnitude = std::sqrt(joypadX * joypadX + joypadY * joypadY);
        if (magnitude > 0) {
            joypadX /= magnitude;
            joypadY /= magnitude;
        }

        // Calculate target velocity based on joystick input
        sf::Vector2f targetVelocity = {joypadX * PLAYER_MOVEMENT_SPEED, joypadY * PLAYER_MOVEMENT_SPEED};

        // Smoothly interpolate towards the target velocity
        if (targetVelocity.x != 0.0f || targetVelocity.y != 0.0f) {
            // Accelerate towards the target velocity
            currentVelocity.x += (targetVelocity.x - currentVelocity.x) * (ACCELERATION / 100.0f);
            currentVelocity.y += (targetVelocity.y - currentVelocity.y) * (ACCELERATION / 100.0f);
        } else {
            // Decelerate to zero if no joystick input
            currentVelocity.x *= (1.0f - DECELERATION / 100.0f);
            currentVelocity.y *= (1.0f - DECELERATION / 100.0f);
        }

        // Apply the velocity to the player
        vel = currentVelocity;
    } else {

        // Variables to store the current velocity
        sf::Vector2f currentVelocity = {0.0f, 0.0f};

        // Determine target velocity based on keyboard input
        sf::Vector2f targetVelocity = {0.0f, 0.0f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            targetVelocity.y = PLAYER_MOVEMENT_SPEED;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            targetVelocity.y = -PLAYER_MOVEMENT_SPEED;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            targetVelocity.x = -PLAYER_MOVEMENT_SPEED;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            targetVelocity.x = PLAYER_MOVEMENT_SPEED;
        }

        // Normalize target velocity to ensure consistent speed
        float magnitude = std::sqrt(targetVelocity.x * targetVelocity.x + targetVelocity.y * targetVelocity.y);
        if (magnitude > 0) {
            targetVelocity.x /= magnitude;
            targetVelocity.y /= magnitude;
            targetVelocity.x *= PLAYER_MOVEMENT_SPEED;
            targetVelocity.y *= PLAYER_MOVEMENT_SPEED;
        }

        // Smoothly interpolate towards the target velocity
        if (targetVelocity.x != 0.0f || targetVelocity.y != 0.0f) {
            // Accelerate towards the target velocity
            currentVelocity.x += (targetVelocity.x - currentVelocity.x) * (ACCELERATION / 100.0f);
            currentVelocity.y += (targetVelocity.y - currentVelocity.y) * (ACCELERATION / 100.0f);
        } else {
            // Decelerate to zero if no key input
            currentVelocity.x *= (1.0f - DECELERATION / 100.0f);
            currentVelocity.y *= (1.0f - DECELERATION / 100.0f);
        }

        // Apply the velocity to the player
        vel = currentVelocity;
    }

    // Update player position
    pos.x += vel.x;
    pos.y += vel.y;
    sprite.setPosition(pos.x, pos.y);

    // Keep player on screen
    ConstrainToScreen();
}

void Player::AddToWallet(int amount) {
    wallet += amount;
}

int Player::GetWalletValue() const {
    return wallet;
}
