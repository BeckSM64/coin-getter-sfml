#include "EnemyManager.h"
#include "Globals.h"

EnemyManager::EnemyManager() {

    for (int i = 0; i < getRandomNumber(5, 20); i++) {
        enemyCollection.push_back(new Enemy());
    }
}

EnemyManager::~EnemyManager() {

    for (Enemy *enemy : enemyCollection) {
        delete(enemy);
        enemy = nullptr;
    }
}

void EnemyManager::Update() {

    for (Enemy *enemy : enemyCollection) {
        enemy->Update();
    }
}

void EnemyManager::Draw(sf::RenderWindow &win) {

    for (Enemy *enemy : enemyCollection) {
        enemy->Draw(win);
    }
}
