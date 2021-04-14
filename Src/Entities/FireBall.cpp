//
// Created by Niccolo on 14/03/2021.
//

#include <list>
#include "AnimationManager.h"

#include "FireBall.h"

FireBall::FireBall(std::string id) :
    Bullet(EntityType::FireBullet, id) {
}

FireBall::~FireBall() {
}

void FireBall::init() {
    setDamage(50);
}

void FireBall::update(int32_t delta_time) {
    if(!isStarted()) {
        playAnimation("DEFAULT", true);
        setStarted(true);
    }
    Entity::update(delta_time);
}

void FireBall::event(GameEvent event, Entity *collider) {
    if(GameEvent::Collision == event) {
        if (collider->getType() == EntityType::Hero)
            setDestroyed();
    }
    else if (event == GameEvent::OutOfBound) {
        setDestroyed();
    }
}

