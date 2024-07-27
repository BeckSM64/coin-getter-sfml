#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.h"
#include "Globals.h"
#include "MainMenu.h"
#include "MainGameScreen.h"

Game::Game() {

    // Create window and set fixed frame rate limit
    win.create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen Window", sf::Style::Fullscreen);
    win.setFramerateLimit(60);

    // Set taskbar icon
    sf::Image icon;
    icon.loadFromFile("sprites/player.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Default to main menu
    currentGameState = GameState::MAIN_MENU;

     // Default to main menu
    currentScreen = std::make_shared<MainMenu>();
}

Game::~Game() {

}

void Game::Run() {

    while(win.isOpen()) {

        // Background color
        sf::Color color = sf::Color(20, 15, 36, 255);

        // Clear the screen with background color
        win.clear(color);

        // Check for events
        Update();
        Draw(win);

        // Update screen based on game state
        switch (currentGameState) {
            case GameState::MAIN_MENU:
                if (std::dynamic_pointer_cast<MainMenu>(currentScreen) == nullptr) {
                    currentScreen = std::make_shared<MainMenu>();
                }
                break;

            case GameState::MAIN_GAME:
                if (std::dynamic_pointer_cast<MainGameScreen>(currentScreen) == nullptr) {
                    currentScreen = std::make_shared<MainGameScreen>();
                }
                break;

            case GameState::QUIT_GAME:
                win.close(); // Exit
                break;

            default:
                // Shouldn't get here
                break;
        }

        // Show everything
        win.display();
    }
}

void Game::Update() {
    currentScreen->Update();
    currentGameState = currentScreen->GetGameState();

    sf::Event event;
    while(win.pollEvent(event)) {

        // Check if window is being closed
        if(event.type == sf::Event::Closed) {
            win.close();
        }
    }
}

void Game::Draw(sf::RenderWindow &win) {
    currentScreen->Draw(win);
}
