#pragma once
#include <SFML/Graphics.hpp>

class HealthBar {

    private:
        const sf::Vector2f HEALTH_BAR_POSITION = sf::Vector2f(10, 10);
        const sf::Vector2f HEALTH_BAR_SIZE = sf::Vector2f(200.0f, 50.0f);
        const sf::Vector2f HEALTH_BAR_BORDER_PADDING = sf::Vector2f(5.0f, 5.0f);
        sf::RectangleShape bar;
        sf::RectangleShape barBorder;
        sf::RectangleShape barBackground;
    
    public:
        HealthBar();
        ~HealthBar();
        void Draw(sf::RenderWindow &win);
        void Update(int playerHealth);
};