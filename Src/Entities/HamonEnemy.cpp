//
// Created by angiolo99 on 29/01/20.
//

#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(EntityType::HamonEnemy, id) {
}

HamonEnemy::~HamonEnemy() {

}

void HamonEnemy::init() {
    setDamage(70);
    setLifeBonus(10);
}

void HamonEnemy::update(int32_t delta_time) {
    if(!isStarted()) {
        changeState(State::Idle);
        setStarted(true);
    }
    Enemy::update(delta_time);
}

void HamonEnemy::changeState(Enemy::State new_state) {
    if(new_state != m_state) {
        switch(new_state) {
            case State::Idle:
                playAnimation("IDLE");
                break;
            case State::Attack:
                playAnimation("THROW");
                break;
            case State::Dead:
                playAnimation("DEATH");
                setEnabled(false);
                break;
            default:
                break;
        }
    }
    m_state = new_state;
}
