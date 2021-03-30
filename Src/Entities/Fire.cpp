//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "ResourceManager.h"
#include "AnimationManager.h"

#include "Fire.h"

Fire::Fire(const std::string& id) :
    Obstacle(EntityType::Wall, id) {
}

Fire::~Fire() {

}

void Fire::init() {
    const std::list<FrameParams> frames = {
            {8, "Fire", {0,0,32,32}, {64,64}, {false, false}},
            {8, "Fire", {32,0,32,32}, {64,64}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(1);
}

void Fire::event(GameEvent event, Entity *collider) {
}
