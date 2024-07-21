#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"

Game::Game() {
    win.create(sf::VideoMode::getDesktopMode(), "SFML Fullscreen Window", sf::Style::Fullscreen);
    mainMenu = new MainMenu();
}

Game::~Game() {
    delete(mainMenu);
    mainMenu = nullptr;
}

void Game::Run() {

    while(win.isOpen()) {

        // Update everything on screen
        Update();

        // Draw everything to the window
        Draw();
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

    // Update everything on window
    mainMenu->Update();
}

void Game::Draw() {

    // Background color
    sf::Color color = sf::Color(20, 15, 36, 255);

    // Clear the screen with background color
    win.clear(color);

    // Draw your objects here
    mainMenu->Draw(win);

    // Show everything
    win.display();
}
