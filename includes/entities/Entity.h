#pragma once
#include <SFML/Graphics.hpp>

class Entity {

    public:
        virtual void Update() = 0;
        void Draw(sf::RenderWindow &win);
        ~Entity() = default;

    protected:
        sf::Sprite sprite;
        sf::Vector2f pos;
        sf::Vector2f vel;
        Entity() = default;
        void DrawEntityImage(sf::RenderWindow &win);
        void ConstrainToScreen();
};
