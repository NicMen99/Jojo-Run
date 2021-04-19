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
    ~HamonEnemy() override;
    void init();
    void update(int32_t delta_time) override;

protected:
    void changeState(Enemy::State new_state) override;

private:
    sf::Time m_shootTime;
    sf::Clock m_shootTimer;
    int m_shoot_left = 1;
};

#endif //JOJO_RUN_HAMONENEMY_H
