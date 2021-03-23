//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(GameObjectType::Weapon, "Weapons")
{

}

void Weapon::init() {
    addTexture("DEFAULT", {"knifeTexture", {0, 0}, false, false});
    setSpeed({0.f, 0.f});
    setQuantity(2);
    updateSprite("DEFAULT");
}

void Weapon::collision(GameObject *collider) {
    setDestroyed();
}
