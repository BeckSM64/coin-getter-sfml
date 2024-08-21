#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "CoinManager.h"
#include "EnemyManager.h"
#include "Screen.h"
#include "Entity.h"
#include "Hud.h"

class MainGameScreen : public CoinGetter::Screen {

    private:
        std::unique_ptr<Entity> player;
        CoinManager *coinManager;
        EnemyManager *enemyManager;
        GameState currentGameState;
        sf::Sound backgroundMusic;
        void GetUserInput();
        void CollisionDetection();
        Player* GetPlayer();
        void HandleEnemyCollision();
        sf::Clock invinsibilityClock;
        const sf::Time invinsibilityCooldown = sf::milliseconds(2000); // 2s cooldown
        Hud hud;

    public:
        MainGameScreen();
        ~MainGameScreen();
        void Draw(sf::RenderWindow &win);
        void Update();
        GameState GetGameState();
        void SetGameState(GameState gameState) override;
};
