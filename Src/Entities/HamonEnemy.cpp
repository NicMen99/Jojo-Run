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
    Enemy::update(delta_time);
    if(!isStarted()) {
        setStarted(true);
    }
}

