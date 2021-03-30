//
// Created by angiolo99 on 23/01/20.
//

#include <list>
#include "Game.h"
#include "AnimationManager.h"

#include "Block.h"


Block::Block(const std::string& id) :
    Obstacle(EntityType::Block, id) {

}

Block::~Block(){

}

void Block::init() {
    const std::list<FrameParams> frames = {
            {1, "blockTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(70);
}

void Block::event(GameEvent event, Entity *collider) {
    if(collider->getType() == EntityType::Hero) {
        setDestroyed();
    }
}

