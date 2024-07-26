#pragma once
#include <SFML/Graphics.hpp>

class Player {

    private:
        sf::Texture playerTexture;
        sf::Sprite playerSprite;
        void DrawPlayerImage(sf::RenderWindow &win);
        sf::Vector2f pos;
        sf::Vector2f vel;

    public:
        Player();
        ~Player();
        void Draw(sf::RenderWindow &win);
        void Update();
};
