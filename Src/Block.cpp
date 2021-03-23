//
// Created by angiolo99 on 23/01/20.
//
#include "Game.h"
#include "GameResourceManager.h"
#include "Block.h"


Block::Block(const std::string& id) :
    Obstacle(GameObjectType::Block, id) {

}

void Block::init() {
    addTexture("DEFAULT", {"blockTexture", {50, 85}});
    setSpeed({0.f, 0.f});
    setDamage(70);
}

void Block::collision(GameObject *collider) {
    if(collider->getType() == GameObjectType::Hero) {
        setDestroyed();
    }
}

