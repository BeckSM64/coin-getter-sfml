#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include "MainMenuScreen.h"
#include "CoinManager.h"
#include "ResourceManager.h"
#include "SettingsManager.h"

MainMenuScreen::MainMenuScreen() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Create title text
    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_128);
    titleText = sf::Text("[COIN GETTER]", font, static_cast<int>(scaledFontSize));
    titleText.setFillColor(sf::Color::White);

    // Position title text
    titleText.setPosition(
        (screenResolution.x / 2 - (titleText.getGlobalBounds().width / 2)),
        (screenResolution.y / 2 - (titleText.getGlobalBounds().height / 2))
    );

    timer = TIME_TO_DELAY_TITLE_COLOR_CHANGE;
    navigationTimer = TIME_TO_DELAY_MENU_NAVIGATION;

    const sf::Texture &playerTexture = ResourceManager::GetInstance().GetTexture("player");

    playerSprite.setTexture(playerTexture);
    
    // Get scale factor from ResourceManager
    float scaleFactor = ResourceManager::GetInstance().GetScaleFactor();
    playerSprite.setScale(scaleFactor * 2.5, scaleFactor * 2.5);

    playerSprite.setPosition(
        screenResolution.x - ((playerSprite.getGlobalBounds().width / 4) * 3),
        screenResolution.y - (playerSprite.getGlobalBounds().height / 2)
    );

    scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(MENU_OPTIONS_FONT_SIZE);
    startGameOption = sf::Text("START", font, scaledFontSize);
    highScoresOption = sf::Text("HIGHSCORES", font, scaledFontSize);
    controlsOption = sf::Text("CONTROLS", font, scaledFontSize);
    optionsOption = sf::Text("OPTIONS", font, scaledFontSize);
    quitOption = sf::Text("QUIT", font, scaledFontSize);

    startGameOption.setPosition(0, 0);
    highScoresOption.setPosition(0, startGameOption.getPosition().y + scaledFontSize);
    controlsOption.setPosition(0, highScoresOption.getPosition().y + scaledFontSize);
    optionsOption.setPosition(0, controlsOption.getPosition().y + scaledFontSize);
    quitOption.setPosition(0, optionsOption.getPosition().y + scaledFontSize);

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
    backgroundMusic.setLoop(true);
    int volume = SettingsManager::GetInstance().GetVolume();
    backgroundMusic.setVolume(volume);
}

MainMenuScreen::~MainMenuScreen() {
    delete(coinManager);
    coinManager = nullptr;
}

void MainMenuScreen::Run() {

}

void MainMenuScreen::Update() {

    ChangeTitleColor();
    GetUserInput();
    coinManager->Update();
}

void MainMenuScreen::Draw(sf::RenderWindow &win) {
    win.draw(titleText);
    DrawPlayerImage(win);
    DrawMenuOptions(win);
    coinManager->Draw(win);
}

void MainMenuScreen::ChangeTitleColor() {

    // Update title color
    titleText.setFillColor(
        sf::Color(
            ResourceManager::GetInstance().GetRandomNumber(0, 255),
            ResourceManager::GetInstance().GetRandomNumber(0, 255),
            ResourceManager::GetInstance().GetRandomNumber(0, 255)
        )
    );
}

void MainMenuScreen::DrawPlayerImage(sf::RenderWindow &win) {
    win.draw(playerSprite);
}

void MainMenuScreen::DrawMenuOptions(sf::RenderWindow &win) {

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

void MainMenuScreen::GetUserInput() {

    float joypadY = 0.0f;
    bool isStartCurrentlyPressed = false;

    if (keyPressClock.getElapsedTime() >= keyPressCooldown) {

        // Check if joystick 0 is connected
        if (sf::Joystick::isConnected(0)) {
        
            joypadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

            if (joypadY > 10.0f) {
                if (currentMenuOption == (menuOptions.size() - 1)) {
                    currentMenuOption = 0;
                } else {
                    currentMenuOption += 1;
                }
                keyPressClock.restart();

            } else if (joypadY < -10.0f) {
                
                if (currentMenuOption == 0) {
                    currentMenuOption = (menuOptions.size() - 1);
                } else {
                    currentMenuOption -= 1;
                }
                keyPressClock.restart();
            }

            // Check if the Enter key is released
            isStartCurrentlyPressed = sf::Joystick::isButtonPressed(0, 2); // Check if button 2 is pressed

        } else {

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

            // Check if the Enter key is released
            isStartCurrentlyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        }
    }

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
                currentGameState = GameState::OPTIONS_MENU;
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

GameState MainMenuScreen::GetGameState() {
    return currentGameState;
}
