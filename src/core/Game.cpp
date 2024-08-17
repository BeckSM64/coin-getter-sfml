#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.h"
#include "Globals.h"
#include "MainMenuScreen.h"
#include "MainGameScreen.h"
#include "OptionsScreen.h"
#include "PauseMenuScreen.h"
#include "DebugMenuScreen.h"
#include "ResourceManager.h"
#include "ControllerManager.h"
#include "SettingsManager.h"
#include <iostream>

Game::Game() {

    // Initialize settings from settings file
    SettingsManager &settingsManager = SettingsManager::GetInstance();
    settingsManager.InitializeSettings();
    sf::Vector2f screenResolution = settingsManager.GetResolution();
    sf::Uint32 displayMode = settingsManager.GetDisplayMode();

    // Create window and set fixed frame rate limit
    win.create(sf::VideoMode(screenResolution.x, screenResolution.y), "[COIN GETTER]", displayMode);
    win.setFramerateLimit(60);

    // Initialize the view to match the window size
    view.setSize(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y));
    view.setCenter(static_cast<float>(win.getSize().x) / 2, static_cast<float>(win.getSize().y) / 2);

    // Background color
    backgroundColor = sf::Color(20, 15, 36, 255);

    // Initialize resources
    ResourceManager::GetInstance().InitializeResources();
    ResourceManager::GetInstance().SetScreenResolution(win.getSize());

    // Set window and taskbar icon
    sf::Image &icon = ResourceManager::GetInstance().GetIcon("coinGetterIcon");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Default to main menu
    currentGameState = GameState::MAIN_MENU;

    // Default to main menu
    currentScreen = std::make_shared<MainMenuScreen>();

    // Delay for screen transitions
    stateTransitionCooldown = sf::milliseconds(200);

    isScreenTransitioning = false;
    screenStack.push(currentScreen);
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

    // TODO: Not sure this should be public, but need to
    // prevent this code from running during screen transitions.
    // Consider reworking screen interface and derived classes
    // to call this from the derived classes' Update() method
    if (isScreenTransitioning) {
        if (stateTransitionClock.getElapsedTime() > stateTransitionCooldown) {
            stateTransitionClock.restart();
            isScreenTransitioning = false;
        }
    } else {
        currentScreen->GetUserInput();
    }
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

    currentScreen = screenStack.top(); // TODO: Seems awfully inefficient

    // Update screen based on game state
    switch (currentGameState) {
        case GameState::MAIN_MENU:
            if (std::dynamic_pointer_cast<MainMenuScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<MainMenuScreen>();
                stateTransitionClock.restart();
                isScreenTransitioning = true;

                // Whenever we go back to the main menu, we should remove
                // all other saved screens from the screen stack
                while (!screenStack.empty()) {
                    screenStack.pop();
                }
                screenStack.push(currentScreen);
            }
            break;

        case GameState::MAIN_GAME:
            if (std::dynamic_pointer_cast<MainGameScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<MainGameScreen>();
                stateTransitionClock.restart();
                isScreenTransitioning = true;

                // Whenever we start a new game, we should remove
                // all other saved screens from the screen stack
                while (!screenStack.empty()) {
                    screenStack.pop();
                }
                screenStack.push(currentScreen);
            }
            break;

        case GameState::OPTIONS_MENU:
            if (std::dynamic_pointer_cast<OptionsScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<OptionsScreen>();
                stateTransitionClock.restart();
                isScreenTransitioning = true;
                screenStack.push(currentScreen);
            }
            break;

        case GameState::PAUSE_MENU:
            if (std::dynamic_pointer_cast<PauseMenuScreen>(currentScreen) == nullptr) {
                currentScreen = std::make_shared<PauseMenuScreen>();
                stateTransitionClock.restart();
                isScreenTransitioning = true;
                screenStack.push(currentScreen);
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