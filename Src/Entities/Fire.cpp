//
// Created by angiolo99 on 23/01/20.
//

#include "Fire.h"

Fire::Fire(const std::string& id) :
    Obstacle(EntityType::Wall, id) {
}

Fire::~Fire() {
}

void Fire::init() {
    setSpeed({0.f, 0.f});
    setDamage(1);
}

void Fire::update(int32_t delta_time) {
    if(!isStarted()) {
        playAnimation("DEFAULT", true);
        setStarted(true);
    }
    Entity::update(delta_time);
}

void Fire::event(GameEvent event, Entity *collider) {
    if(GameEvent::Collision == event ) {
        if (collider->getType() == EntityType::Hero)
            setEnabled(false);
    }
    else if (event == GameEvent::OutOfBound) {
        setDestroyed();
    }
}
