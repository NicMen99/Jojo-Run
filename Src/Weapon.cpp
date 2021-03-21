//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(GameObjectType::Weapon, "Weapons")
{

}

void Weapon::init() {
    addTexture("DEFAULT", {"knifeTexture", false, {1.f,1.f}, {0,0,0,0}});
    setSpeed({0.f, 0.f});
    setQuantity(2);
    updateSprite("DEFAULT");
}

void Weapon::collision(GameObject *collider) {
    setDestroyed();
}
