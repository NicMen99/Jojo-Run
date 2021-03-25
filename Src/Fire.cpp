//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Fire.h"

Fire::Fire(const std::string& id) :
    Obstacle(GameObjectType::Wall, id) {
}

void Fire::init() {
    auto animation = m_animator.createAnimation();
    animation->addFrame("Fire", {0,0,32,32}, 8, {64, 64});
    animation->addFrame("Fire", {32,0,32,32}, 8, {64, 64});

    m_animator.play();
    setSpeed({0.f, 0.f});
    setDamage(10);
}

void Fire::collision(GameObject *collider) {
}