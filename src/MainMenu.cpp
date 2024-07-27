#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Globals.h"
#include "MainMenu.h"
#include "CoinManager.h"
#include "ResourceManager.h"

MainMenu::MainMenu() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

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

    const sf::Texture &playerTexture = ResourceManager::GetInstance().GetTexture("player");

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
    currentGameState = GameState::MAIN_MENU;

    coinManager = new CoinManager();

    wasStartPressed = false;

    // Play game audio
    const sf::SoundBuffer &soundBuffer = ResourceManager::GetInstance().GetSoundBuffer("endo");
    backgroundMusic.setBuffer(soundBuffer);
    backgroundMusic.play();
}

MainMenu::~MainMenu() {
    delete(coinManager);
    coinManager = nullptr;
}

void MainMenu::Run() {

}

void MainMenu::Update() {

    ChangeTitleColor();
    GetUserInput();
    coinManager->Update();
}

void MainMenu::Draw(sf::RenderWindow &win) {
    win.draw(titleText);
    DrawPlayerImage(win);
    DrawMenuOptions(win);
    coinManager->Draw(win);
}

void MainMenu::ChangeTitleColor() {

    // Update title color
    titleText.setFillColor(
        sf::Color(
            getRandomNumber(0, 255),
            getRandomNumber(0, 255),
            getRandomNumber(0, 255)
        )
    );
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

    if (keyPressClock.getElapsedTime() >= keyPressCooldown) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            if (currentMenuOption == (menuOptions.size() - 1)) {
                currentMenuOption = 0;
            } else {
                currentMenuOption += 1;
            }
            keyPressClock.restart();

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            if (currentMenuOption == 0) {
                currentMenuOption = (menuOptions.size() - 1);
            } else {
                currentMenuOption -= 1;
            }
            keyPressClock.restart();
        }
    }

    // Check if the Enter key is released
    bool isStartCurrentlyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

    // Check if the start button was pressed and released
    if (!isStartCurrentlyPressed && wasStartPressed) {

        // Check which option was selected
        switch (currentMenuOption) {
            case menuOptionsEnum::START:

                // Start new game
                currentGameState = GameState::MAIN_GAME;
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

    // Update the previous state
    wasStartPressed = isStartCurrentlyPressed;
}

GameState MainMenu::GetGameState() {
    return currentGameState;
}
