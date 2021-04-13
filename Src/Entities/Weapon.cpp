//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(EntityType::Weapon, "Weapons") {
}

Weapon::~Weapon() {
}

void Weapon::init() {
    setSpeed({0.f, 0.f});
    setGain(2);
}

void Weapon::event(GameEvent event, Entity *collider) {
    if (event == GameEvent::Collection) {
        setDestroyed();
    }
    else if (event == GameEvent::OutOfBound) {
        setDestroyed();
    }
}
