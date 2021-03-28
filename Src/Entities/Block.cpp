//
// Created by angiolo99 on 23/01/20.
//
#include "Game.h"
#include "ResourceManager.h"
#include "Block.h"


Block::Block(const std::string& id) :
    Obstacle(GameObjectType::Block, id) {

}

void Block::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "blockTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(70);
}

void Block::collision(Entity *collider) {
    if(collider->getType() == GameObjectType::Hero) {
        setDestroyed();
    }
}

