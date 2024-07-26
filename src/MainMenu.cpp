#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "MainMenu.h"

MainMenu::MainMenu() {

    // Load font with path relative to output directory of generated executable
    if(!this->font.loadFromFile("./fonts/RetroComputer.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Create title text
    titleText = sf::Text("[COIN GETTER]", font, 128);
    titleText.setFillColor(sf::Color::White);

    // Position title text
    titleText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (titleText.getGlobalBounds().width / 2)),
        (sf::VideoMode::getDesktopMode().height / 2 - (titleText.getGlobalBounds().height / 2))
    );

    timer = TIME_TO_DELAY_TITLE_COLOR_CHANGE;
    navigationTimer = TIME_TO_DELAY_MENU_NAVIGATION;

    if (!playerTexture.loadFromFile("sprites/player.png"))
    {
        std::cout << "DIDNT LOAD PLAYER IMAGE" << std::endl;
    } else {
        std::cout << "LOADED PLAYER IMAGE" << std::endl;
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(sf::Vector2f(2.5f, 2.5f));
    playerSprite.setPosition(
        sf::VideoMode::getDesktopMode().width - ((playerSprite.getGlobalBounds().width / 4) * 3),
        sf::VideoMode::getDesktopMode().height - (playerSprite.getGlobalBounds().height / 2)
    );

    startGameOption = sf::Text("START", font, MENU_OPTIONS_FONT_SIZE);
    highScoresOption = sf::Text("HIGHSCORES", font, MENU_OPTIONS_FONT_SIZE);
    controlsOption = sf::Text("CONTROLS", font, MENU_OPTIONS_FONT_SIZE);
    optionsOption = sf::Text("OPTIONS", font, MENU_OPTIONS_FONT_SIZE);
    quitOption = sf::Text("QUIT", font, MENU_OPTIONS_FONT_SIZE);

    startGameOption.setPosition(0, 0);
    highScoresOption.setPosition(0, startGameOption.getPosition().y + MENU_OPTIONS_FONT_SIZE);
    controlsOption.setPosition(0, highScoresOption.getPosition().y + MENU_OPTIONS_FONT_SIZE);
    optionsOption.setPosition(0, controlsOption.getPosition().y + MENU_OPTIONS_FONT_SIZE);
    quitOption.setPosition(0, optionsOption.getPosition().y + MENU_OPTIONS_FONT_SIZE);

    menuOptions.push_back(startGameOption);
    menuOptions.push_back(highScoresOption);
    menuOptions.push_back(controlsOption);
    menuOptions.push_back(optionsOption);
    menuOptions.push_back(quitOption);

    currentMenuOption = menuOptionsEnum::START;// Default to START OPTION
    currentGameState = GameState::MAIN_MENU; // TODO: Look for better way to handle this than in every "screen"
}

MainMenu::~MainMenu() {

}

void MainMenu::Run() {

}

void MainMenu::Update() {

    ChangeTitleColor();
    GetUserInput();
}

void MainMenu::Draw(sf::RenderWindow &win) {
    win.draw(titleText);
    DrawPlayerImage(win);
    DrawMenuOptions(win);
}

void MainMenu::ChangeTitleColor() {

    if ( timer <= 0 ) {
        // Update title color
        titleText.setFillColor(
            sf::Color(
                getRandomNumber(0, 255),
                getRandomNumber(0, 255),
                getRandomNumber(0, 255)
            )
        );
        timer = TIME_TO_DELAY_TITLE_COLOR_CHANGE; // Reset timer
    }
    timer -= 1; // Decrement timer
}

void MainMenu::DrawPlayerImage(sf::RenderWindow &win) {
    win.draw(playerSprite);
}

void MainMenu::DrawMenuOptions(sf::RenderWindow &win) {

    // Iterate over list of options and draw them
    for ( int i = 0; i < menuOptions.size(); i++ ) {

        // If the option is currently being hovered over, render red
        if ( i == currentMenuOption ) {
            menuOptions[i].setFillColor(sf::Color::Red);
        } else {
            menuOptions[i].setFillColor(sf::Color::White);
        }
        win.draw(menuOptions[i]);
    }
}

void MainMenu::GetUserInput() {

    if ( navigationTimer <= 0 ) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            if (currentMenuOption == (menuOptions.size() - 1)) {
                currentMenuOption = 0;
            } else {
                currentMenuOption += 1;
            }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            if (currentMenuOption == 0) {
                currentMenuOption = (menuOptions.size() - 1);
            } else {
                currentMenuOption -= 1;
            }
        }
        navigationTimer = TIME_TO_DELAY_MENU_NAVIGATION; // Reset timer
    }
    navigationTimer -= 1; // Decrement timer

    // Check which option was selected
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        // Check which option was selected
        switch (currentMenuOption) {
            case menuOptionsEnum::START:
                // Start new game
                break;
            case menuOptionsEnum::HIGHSCORES:
                // Go to high score screen
                break;
            case menuOptionsEnum::OPTIONS:
                // Go to options screen
                break;
            case menuOptionsEnum::CONTROLS:
                // GO to controls scree
                break;
            case menuOptionsEnum::QUIT:
                // Quit
                currentGameState = GameState::QUIT_GAME;
                break;
            default:
                // Shouldn't get here
                break;
        }
    }
}

GameState MainMenu::GetGameState() {
    return currentGameState;
}
