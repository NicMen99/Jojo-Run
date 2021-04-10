//
// Created by Niccolo on 25/02/2021.
//

#include "Platform.h"

Platform::Platform(std::string id) :
    Entity(EntityGroup::Platform, EntityType::Platform, std::move(id)) {
}

Platform::~Platform() {
}

void Platform::init(EntityType type) {
    if(EntityType::StonePlatform == type) {
        setSpeed(0, 0);
    }
}

void Platform::event(GameEvent event, Entity *collider) {
    if (event == GameEvent::OutOfBound) {
        setDestroyed();
    }
}
