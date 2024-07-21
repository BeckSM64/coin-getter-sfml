#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu {

    private:
        sf::Font font;
        sf::Text titleText;
        sf::Texture playerTexture;
        sf::Sprite playerSprite;
        int timer;
        sf::Text startGameOption;
        sf::Text highScoresOption;
        sf::Text controlsOption;
        sf::Text optionsOption;
        std::vector<sf::Text> menuOptions;
        void ChangeTitleColor();
        void DrawPlayerImage(sf::RenderWindow &win);
        void DrawMenuOptions(sf::RenderWindow &win);

    public:
        MainMenu();
        ~MainMenu();
        void Run();
        void Update();
        void Draw(sf::RenderWindow &win);
};
