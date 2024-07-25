#pragma once
#include <SFML/Graphics.hpp>

class Player {

    private:
        sf::Texture playerTexture;
        sf::Sprite playerSprite;
        void DrawPlayerImage(sf::RenderWindow &win);

    public:
        Player();
        ~Player();
        void Draw(sf::RenderWindow &win);
        void Update();
};
