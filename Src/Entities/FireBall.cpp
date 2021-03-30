//
// Created by Niccolo on 14/03/2021.
//

#include "FireBall.h"

FireBall::FireBall(std::string id) :
    Bullet(GameObjectType::FireBullet, id) {

}

FireBall::~FireBall() {

}

void FireBall::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "fireBlockTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(50);
}

void FireBall::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void FireBall::event(GameEvent event, Entity *collider) {
    Entity::event(GameEvent::Collision, collider);
    if (collider->getType() == GameObjectType::Hero)
        setDestroyed();
}

