//
// Created by Niccolo on 14/03/2021.
//

#include "Emerald.h"

Emerald::Emerald(const std::string& id) :
    Bullet(GameObjectType::EmeraldBullet, id) {}

void Emerald::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "emeraldBlockTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(150);
}

void Emerald::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void Emerald::event(GameEvent event, Entity *collider) {
    Entity::event(GameEvent::Collision, collider);
    if (collider->getType() == GameObjectType::Hero)
        setDestroyed();
}

