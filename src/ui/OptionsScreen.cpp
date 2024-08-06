#include <memory>
#include "OptionsScreen.h"
#include "ResourceManager.h"
#include "ScreenStyleOptionSelector.h"
#include "ResolutionOptionSelector.h"
#include "Globals.h"

OptionsScreen::OptionsScreen() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    std::map<int, std::string> videoOptionIdToOptionStringMap;
    videoOptionIdToOptionStringMap[0] = "1920x1080";
    videoOptionIdToOptionStringMap[1] = "1600x900";
    videoOptionIdToOptionStringMap[2] = "1280x720";
    videoOptionSelector = std::make_unique<ResolutionOptionSelector>(videoOptionIdToOptionStringMap, sf::Vector2f(0, 0));

    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_72);
    optionsSreenTitleText = sf::Text("[OPTIONS]", font, scaledFontSize);
    optionsSreenTitleText.setPosition(
        sf::Vector2f(
            (screenResolution.x / 2) - (optionsSreenTitleText.getGlobalBounds().width / 2),
            0
        )
    );

    currentGameState = GameState::OPTIONS_MENU;
}

OptionsScreen::~OptionsScreen() {

}

void OptionsScreen::Draw(sf::RenderWindow & win) {
    win.draw(optionsSreenTitleText);
    videoOptionSelector->Draw(win);
}

void OptionsScreen::Update() {
    videoOptionSelector->Update();
}

void OptionsScreen::GetUserInput() {

}

GameState OptionsScreen::GetGameState() {
    return currentGameState;
}
