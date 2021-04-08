//
// Created by Niccolo on 14/03/2021.
//

#include "Emerald.h"

Emerald::Emerald(const std::string& id) :
    Bullet(EntityType::EmeraldBullet, id) {}

Emerald::~Emerald(){

}

void Emerald::init() {
    setDamage(150);
}

void Emerald::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void Emerald::event(GameEvent event, Entity *collider) {
    if(GameEvent::Collision == event ) {
        if (collider->getType() == EntityType::Hero)
            setDestroyed();
    }
}

