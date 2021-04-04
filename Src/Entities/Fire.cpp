//
// Created by angiolo99 on 23/01/20.
//

#include "Fire.h"

Fire::Fire(const std::string& id) :
    Obstacle(EntityType::Wall, id) {
}

Fire::~Fire() {

}

void Fire::init() {
    setSpeed({0.f, 0.f});
    setDamage(1);
}

void Fire::event(GameEvent event, Entity *collider) {
}
