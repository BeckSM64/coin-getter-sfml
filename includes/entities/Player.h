#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity {

    public:
        Player();
        void Update() override;
};
