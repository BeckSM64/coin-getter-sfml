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
        int navigationTimer;
        sf::Text startGameOption;
        sf::Text highScoresOption;
        sf::Text controlsOption;
        sf::Text optionsOption;
        sf::Text quitOption;
        std::vector<sf::Text> menuOptions;
        enum menuOptionsEnum {
            START,
            HIGHSCORES,
            CONTROLS,
            OPTIONS,
            QUIT
        };
        int currentMenuOption;
        void ChangeTitleColor();
        void DrawPlayerImage(sf::RenderWindow &win);
        void DrawMenuOptions(sf::RenderWindow &win);
        void GetUserInput();

    public:
        MainMenu();
        ~MainMenu();
        void Run();
        void Update();
        void Draw(sf::RenderWindow &win);
};
