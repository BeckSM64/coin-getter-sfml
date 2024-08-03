#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {

    private:
        std::vector<Enemy> enemyCollection;
        sf::Clock enemySpawnClock;
        sf::Time enemySpawnTimer;
        int enemyRespawnRateInSeconds;

    public:
        EnemyManager();
        ~EnemyManager();
        void Update();
        void Draw(sf::RenderWindow &win);
        std::vector<Enemy>& GetCollection();
};
