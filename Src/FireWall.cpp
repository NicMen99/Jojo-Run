//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "FireWall.h"

FireWall::FireWall(const std::string& id) :
    Obstacle(GameObjectType::Wall, id) {
}

void FireWall::init() {
    addTexture("DEFAULT", {"fireWallTexture", false, {1.0f, 1.0f}, {0, 0, 0, 0}});
    setSpeed({0.f, 0.f});
    setDamage(10);
}

void FireWall::collision(GameObject *collider) {
}