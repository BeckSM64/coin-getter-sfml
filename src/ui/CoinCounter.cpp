#include "CoinCounter.h"
#include "ResourceManager.h"
#include "Globals.h"

CoinCounter::CoinCounter() {

    // Setup font
    const sf::Font &font = ResourceManager::GetInstance().GetFont("retroFont");

    coinCountText = sf::Text("COIN COUNT: 0", font, FONT_SIZE_72);
    coinCountText.setFillColor(sf::Color::White);

    // Position title text
    coinCountText.setPosition(
        (sf::VideoMode::getDesktopMode().width / 2 - (coinCountText.getGlobalBounds().width / 2)),
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
