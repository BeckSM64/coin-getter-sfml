#include "EnemyManager.h"
#include "ResourceManager.h"
#include "Globals.h"

EnemyManager::EnemyManager() {

    // Time between enemy respawns
    enemyRespawnRateInSeconds = 30;

    // Timer to determine when to spawn another enemy
    enemySpawnTimer = sf::seconds(enemyRespawnRateInSeconds);

    // Add an enemy to the collcetion to start
    Enemy enemy;
    enemyCollection.push_back(enemy);
}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Update() {

    // Update enemies in the collection
    for (Enemy &enemy : enemyCollection) {
        enemy.Update();
    }

    // Determine if it's time to spawn a new enemy
    if (enemySpawnClock.getElapsedTime() > enemySpawnTimer) {
        
        Enemy enemy;
        enemyCollection.push_back(enemy);
        enemySpawnClock.restart(); // Reset the clock
    }
}

void EnemyManager::Draw(sf::RenderWindow &win) {

    for (Enemy &enemy : enemyCollection) {
        enemy.Draw(win);
    }
}

std::vector<Enemy>& EnemyManager::GetCollection() {
    return enemyCollection;
}
