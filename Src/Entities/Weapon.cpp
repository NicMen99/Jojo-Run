//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(EntityType::Weapon, "Weapons")
{

}

Weapon::~Weapon() {

}

void Weapon::init() {
    setSpeed({0.f, 0.f});
    setQuantity(2);
}

void Weapon::event(GameEvent event, Entity *collider) {
    setDestroyed();
}
