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
    const std::list<Animation::FrameParams> frames = {
            {8, "Fire", {0,0,32,32}, {64,64}, {false, false}},
            {8, "Fire", {32,0,32,32}, {64,64}, {false, false}}
    };
    m_animator.addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(10);
}

void Fire::collision(GameObject *collider) {
}