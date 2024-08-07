#pragma once
#include <SFML/Graphics.hpp>

class MenuOption {

    public:
        virtual ~MenuOption() = default;
        virtual void Draw(sf::RenderWindow &win) = 0;
        virtual void Update() = 0;
        virtual void GetUserInput() = 0;
        void SetActive(bool active);
        bool GetActive() const;
    
    protected:

        // Make sure it can't be instantiated
        MenuOption() = default;
        bool isActive;
};
