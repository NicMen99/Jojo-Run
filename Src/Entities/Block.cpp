//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "Block.h"


Block::Block(const std::string& id) :
    Obstacle(EntityType::Block, id) {

}

Block::~Block(){

}

void Block::init() {
    setSpeed({0.f, 0.f});
    setDamage(70);
}

void Block::update(int32_t delta_time) {
    if(!isStarted()) {
        playAnimation("DEFAULT", true);
        setStarted(true);
    }
    Entity::update(delta_time);
}

void Block::event(GameEvent event, Entity *collider) {
    if(event == GameEvent::Collision) {
        if(collider->getType() == EntityType::Hero) {
            setDestroyed();
        }
    }
}

