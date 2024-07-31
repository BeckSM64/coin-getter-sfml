#pragma once
#include <SFML/Graphics.hpp>

class Entity {

    public:
        virtual void Update() = 0;
        void Draw(sf::RenderWindow &win);
        sf::FloatRect GetHitbox() const;
        sf::Vector2f GetVelocity() const;
        sf::Vector2f GetPosition() const;
        void SetVelocity(sf::Vector2f velocity);
        void SetPosition(sf::Vector2f position);
        bool IsDamageable() const;
        void SetDamageable(bool damageable);
        ~Entity() = default;

    protected:
        sf::Sprite sprite;
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::FloatRect hitBox;
        bool isDamageable;
        Entity() = default;
        void DrawEntityImage(sf::RenderWindow &win);
        void ConstrainToScreen();
};
