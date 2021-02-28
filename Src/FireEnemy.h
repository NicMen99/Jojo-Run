//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_FIREENEMY_H
#define JOJO_RUN_FIREENEMY_H

#include "Enemy.h"

class FireEnemy final : public Enemy
{
public:
    explicit FireEnemy(const std::string& id);
    ~FireEnemy() override = default;

public:
    std::unique_ptr<Bullet> SpecialAction() override;
};

#endif //JOJO_RUN_FIREENEMY_H
