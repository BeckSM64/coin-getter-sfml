#pragma once
#include <SFML/Graphics.hpp>

class Coin {

    private:
        sf::Texture coinTexture;
        sf::Sprite coinSprite;
        sf::Vector2f pos;
        sf::Vector2f vel;
        void DrawCoinImage(sf::RenderWindow &win);
        void ConstrainToScreen();

    public:
        Coin();
        ~Coin();
        void Draw(sf::RenderWindow &win);
        void Update();
};