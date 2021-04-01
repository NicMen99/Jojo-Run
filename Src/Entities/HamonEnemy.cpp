//
// Created by angiolo99 on 29/01/20.
//

#include <list>
#include "AnimationManager.h"

#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(EntityType::HamonEnemy, id) {
}

HamonEnemy::~HamonEnemy() {

}

void HamonEnemy::init() {
    const std::list<FrameParams> frames = {
            {1, "hamonEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
    };
    addAnimation("DEFAULT", frames);
    setDamage(70);
    setLifeBonus(10);
    addSound("HAMONACTION", "hamonEnemyShout");
}

void HamonEnemy::update(int32_t delta_time) {
    Enemy::update(delta_time);
    if(!isStarted()) {
        setStarted(true);
    }
}

