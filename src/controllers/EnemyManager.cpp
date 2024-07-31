#include "EnemyManager.h"
#include "ResourceManager.h"
#include "Globals.h"

EnemyManager::EnemyManager() {

    for (int i = 0; i < ResourceManager::GetInstance().GetRandomNumber(5, 20); i++) {
        Enemy enemy;
        enemyCollection.push_back(enemy);
    }
}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Update() {

    for (Enemy &enemy : enemyCollection) {
        enemy.Update();
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
