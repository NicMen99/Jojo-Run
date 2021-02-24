//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_EMERALDENEMY_H
#define JOJO_RUN_EMERALDENEMY_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>

class EmeraldEnemy : public Enemy {
public:
    std::unique_ptr<Block> SpecialAction() override;
};

#endif //JOJO_RUN_EMERALDENEMY_H
