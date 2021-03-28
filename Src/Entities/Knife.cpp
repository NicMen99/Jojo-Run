//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "GameConfig.h"
#include "Knife.h"

Knife::Knife(std::string id) :
    Bullet(GameObjectType::Knife, id) {
}

void Knife::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "knifeTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(100);
}

void Knife::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(getPosition().x > CONFIG.getWindowSize().x)
        setDestroyed();
}

void Knife::event(GameEvent event, Entity *collider) {
    Entity::event(GameEvent::Collision, collider);
    setDestroyed();
}





