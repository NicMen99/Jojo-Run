//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_EMERALDENEMY_H
#define JOJO_RUN_EMERALDENEMY_H


#include "Enemy.h"

class EmeraldEnemy final : public Enemy
{
public:
    explicit EmeraldEnemy(std::string id);
    ~EmeraldEnemy() = default;

public:
    std::unique_ptr<Bullet> SpecialAction() override;
};


#endif //JOJO_RUN_EMERALDENEMY_H
