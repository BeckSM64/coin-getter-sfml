#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "CoinManager.h"
#include "EnemyManager.h"
#include "Screen.h"
#include "Entity.h"

class MainGameScreen : public CoinGetter::Screen {

    private:
        std::unique_ptr<Entity> player;
        CoinManager *coinManager;
        EnemyManager *enemyManager;
        bool isPaused;
        bool wasStartPressed;
        sf::Text pauseText;
        GameState currentGameState;
        sf::Sound backgroundMusic;
        void GetUserInput();
        void CollisionDetection();
        Player* GetPlayer();
        void HandleEnemyCollision(std::unique_ptr<Entity>& player, std::vector<Enemy>& enemies);

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        GameState GetGameState();
};
