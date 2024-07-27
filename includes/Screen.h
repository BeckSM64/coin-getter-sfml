#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

namespace CoinGetter {

    // Base class for all screens
    class Screen {
        public:
            // Virtual destructor to ensure proper cleanup of derived classes
            virtual ~Screen() = default;

            // Called when the screen is entered
            //virtual void Enter() = 0;

            // Called when the screen is exited
            //virtual void Exit() = 0;

            // Update logic for the screen
            virtual void Update() = 0;

            // Draw the screen content
            virtual void Draw(sf::RenderWindow& win) = 0;

            // Get the current game state
            virtual GameState GetGameState() = 0;

            // Handle user input
            virtual void GetUserInput() = 0;

        protected:
            // Protected constructor to prevent instantiation of the base class
            Screen() = default;
            GameState currentGameState;
    };
}
