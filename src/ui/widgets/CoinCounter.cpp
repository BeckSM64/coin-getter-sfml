#include "CoinCounter.h"
#include "ResourceManager.h"
#include "Globals.h"

CoinCounter::CoinCounter() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    // Scale the font size based on the current screen resolution
    float scaledFontSize = ResourceManager::GetInstance().ScaleFontSize(FONT_SIZE_72);
    coinCountText = sf::Text("COIN COUNT: 0", font, scaledFontSize);
    coinCountText.setFillColor(sf::Color::White);

    // Get screen resolution from ResourceManager
    sf::Vector2u screenResolution = ResourceManager::GetInstance().GetScreenResolution();

    // Position title text
    coinCountText.setPosition(
        (screenResolution.x / 2 - (coinCountText.getGlobalBounds().width / 2)),
        TOP_OF_SCREEN_PADDING
    );
}

CoinCounter::~CoinCounter() {

}

void CoinCounter::Draw(sf::RenderWindow & win) {

    win.draw(coinCountText);
}

void CoinCounter::Update(int coinCount) {

    coinCountText.setString("COIN COUNT:" + std::to_string(coinCount));
}
