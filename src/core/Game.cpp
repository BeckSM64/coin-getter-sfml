#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.h"
#include "Globals.h"
#include "MainMenuScreen.h"
#include "MainGameScreen.h"
#include "OptionsScreen.h"
#include "DebugMenuScreen.h"
#include "ResourceManager.h"
#include "ControllerManager.h"

Game::Game() {
    // Create window and set fixed frame rate limit
    win.create(sf::VideoMode::getDesktopMode(), "[COIN GETTER]", sf::Style::None);
    win.setFramerateLimit(60);

    // Initialize the view to match the window size
    view.setSize(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y));
    view.setCenter(static_cast<float>(win.getSize().x) / 2, static_cast<float>(win.getSize().y) / 2);

    // Background color
    backgroundColor = sf::Color(20, 15, 36, 255);

    // Set taskbar icon
    sf::Image icon;
    icon.loadFromFile("sprites/player.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Default to main menu
    currentGameState = GameState::MAIN_MENU;

    // Initialize resources
    ResourceManager::GetInstance().InitializeResources();
    ResourceManager::GetInstance().SetScreenResolution(win.getSize());

    // Default to main menu
    currentScreen = std::make_shared<MainMenuScreen>();
}

Game::~Game() {

}

void Game::Run() {
    while (win.isOpen()) {
        // Poll for events
        HandleEvents();

        // Clear the screen with background color
        win.clear(backgroundColor);

        // Update Game Objects
        Update();

        // Draw everything to the screen
        Draw();

        // Handle transitioning to different screens
        ManageGameState();

        // Show everything
        win.display();
    }
}

void Game::Update() {
    currentScreen->Update();
    currentGameState = currentScreen->GetGameState();
}

void Game::Draw() {
    win.setView(view); // Set the view before drawing
    currentScreen->Draw(win);
}

void Game::HandleEvents() {
    sf::Event event;
    while (win.pollEvent(event)) {
        // Check if window is being closed
        if (event.type == sf::Event::Closed) {
            win.close();
        }

        // Check if the window is resized
        if (event.type == sf::Event::Resized) {
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            view.setCenter(static_cast<float>(event.size.width) / 2, static_cast<float>(event.size.height) / 2);
        }
    }
}

void Game::ManageGameState() {
    // Update screen based on game state
    switch (currentGameState) {
        case GameState::MAIN_MENU:
            if (std::dynamic_pointer_cast<MainMenuScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<MainMenuScreen>();
            }
            break;

        case GameState::MAIN_GAME:
            if (std::dynamic_pointer_cast<MainGameScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<MainGameScreen>();
            }
            break;

        case GameState::OPTIONS_MENU:
            if (std::dynamic_pointer_cast<OptionsScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<OptionsScreen>();
            }
            break;

        case GameState::QUIT_GAME:
            win.close(); // Exit
            break;

        default:
            // Shouldn't get here
            break;
    }
}