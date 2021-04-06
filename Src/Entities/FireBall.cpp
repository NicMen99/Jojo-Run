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
    Entity::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void FireBall::event(GameEvent event, Entity *collider) {
    Entity::event(GameEvent::Collision, collider);
    if (collider->getType() == EntityType::Hero)
        setDestroyed();
}

