#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity {

    public:
        Enemy();
        void Update() override;
};
