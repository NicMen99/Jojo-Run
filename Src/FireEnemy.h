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

private:
    void update(int32_t delta_time) override;
    sf::Time m_shootTime;
    sf::Clock m_shootTimer;
    int m_shoot_left = 1;

};

#endif //JOJO_RUN_FIREENEMY_H
