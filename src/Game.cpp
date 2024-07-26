#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Globals.h"
#include "MainMenu.h"
#include "MainGameScreen.h"

Game::Game() {
    win.create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen Window", sf::Style::Fullscreen);
    currentGameState = GameState::MAIN_MENU; // Default to main menu
}

Game::~Game() {

    if (mainMenu != nullptr) {
        delete(mainMenu);
        mainMenu = nullptr;
    }

    if (mainGameScreen != nullptr) {
        delete(mainGameScreen);
        mainGameScreen = nullptr;
    }
}

void Game::Run() {

    while(win.isOpen()) {

        // Background color
        sf::Color color = sf::Color(20, 15, 36, 255);

        // Clear the screen with background color
        win.clear(color);

        // Check for events
        Update();

        switch (currentGameState) {

            case GameState::MAIN_MENU:
                if (mainMenu == nullptr) {
                    mainMenu = new MainMenu();
                }
                mainMenu->Update();
                mainMenu->Draw(win);
                currentGameState = mainMenu->GetGameState();
                break;

            case GameState::MAIN_GAME:
                if (mainGameScreen == nullptr) {
                    mainGameScreen = new MainGameScreen();
                }
                mainGameScreen->Update();
                mainGameScreen->Draw(win);
                break;
            case GameState::QUIT_GAME:
                this->~Game();
                exit(EXIT_SUCCESS);
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

    sf::Event event;
    while(win.pollEvent(event)) {

        // Check if window is being closed
        if(event.type == sf::Event::Closed) {
            win.close();
        }
    }
}
