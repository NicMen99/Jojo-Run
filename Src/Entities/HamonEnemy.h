//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_HAMONENEMY_H
#define JOJO_RUN_HAMONENEMY_H

#include "Entities/Enemy.h"

class HamonEnemy final: public Enemy
{
public:
    explicit HamonEnemy(const std::string& id);
    ~HamonEnemy() override = default;
    void init();
};

#endif //JOJO_RUN_HAMONENEMY_H
