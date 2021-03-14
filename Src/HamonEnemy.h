//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_HAMONENEMY_H
#define JOJO_RUN_HAMONENEMY_H

#include "Enemy.h"

class HamonEnemy final: public Enemy
{
public:
    explicit HamonEnemy(std::string id);
    ~HamonEnemy() override = default;

};

#endif //JOJO_RUN_HAMONENEMY_H
