//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_EMERALDENEMY_H
#define JOJO_RUN_EMERALDENEMY_H


#include "Enemy.h"

class EmeraldEnemy final : public Enemy
{
 public:
    explicit EmeraldEnemy(const std::string& id);
    ~EmeraldEnemy() override;
    void init();
    void update(int32_t delta_time) override;

protected:
    void changeState(Enemy::State new_state) override;

private:
    sf::Time m_shootTime;
    sf::Clock m_shootTimer;
    int m_shoot_left = 1;

};


#endif //JOJO_RUN_EMERALDENEMY_H
