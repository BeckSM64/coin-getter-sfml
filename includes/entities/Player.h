#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Coin.h"

class Player : public Entity {

    private:
        int wallet;

    public:
        Player();
        void Update() override;
        void AddToWallet(int amount);
        int GetWalletValue() const;
};
