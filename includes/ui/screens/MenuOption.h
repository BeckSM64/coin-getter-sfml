#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class MenuOption {

    public:
        virtual ~MenuOption() = default;
        virtual void Draw(sf::RenderWindow &win) = 0;
        virtual void Update() = 0;
        virtual void GetUserInput() = 0;
        void SetActive(bool active);
        bool GetActive() const;
        void SetEnabled(bool enabled);
        bool GetEnabled() const;
    
    protected:

        // Make sure it can't be instantiated
        MenuOption() = default;
        bool isActive;
        bool isEnabled = true; // Set default to true, I don't love this
};
