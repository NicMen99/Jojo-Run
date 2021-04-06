//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "Knife.h"

Knife::Knife(std::string id) :
    Bullet(EntityType::Knife, id) {
}

Knife::~Knife() {

}

void Knife::init() {
    setDamage(100);
}

void Knife::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(getPosition().x > CONFIG->getWindowSize().x)
        setDestroyed();
}

void Knife::event(GameEvent event, Entity *collider) {
    Entity::event(GameEvent::Collision, collider);
    setDestroyed();
}
