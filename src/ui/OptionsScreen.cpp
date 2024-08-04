#include "OptionsScreen.h"
#include "ResourceManager.h"
#include "Globals.h"

OptionsScreen::OptionsScreen() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    optionsSreenTitleText = sf::Text("[OPTIONS]", font, FONT_SIZE_72);
    optionsSreenTitleText.setPosition(
        sf::Vector2f(
            (sf::VideoMode::getDesktopMode().width / 2) - (optionsSreenTitleText.getGlobalBounds().width / 2),
            0
        )
    );

    currentGameState = GameState::OPTIONS_MENU;
}

OptionsScreen::~OptionsScreen() {

}

void OptionsScreen::Draw(sf::RenderWindow & win) {
    win.draw(optionsSreenTitleText);
    videoOptionSelector.Draw(win);
}

void OptionsScreen::Update() {
    videoOptionSelector.Update();
}

void OptionsScreen::GetUserInput() {

}

GameState OptionsScreen::GetGameState() {
    return currentGameState;
}
