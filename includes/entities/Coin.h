#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Coin : public Entity {

    public:
        Coin();
        void Update() override;
};