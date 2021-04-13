//
// Created by angiolo99 on 29/01/20.
//

#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(EntityType::Shield, id) {
}

Shield::~Shield() {
}

void Shield::init() {
    setSpeed({0.f, 0.f});
}

void Shield::event(GameEvent event, Entity *collider) {
    if (event == GameEvent::Collection) {
        setDestroyed();
    }
    else if (event == GameEvent::OutOfBound) {
        setDestroyed();
    }
}
