//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(GameObjectType::Shield, id)
{
}

void Shield::init() {
    addTexture("DEFAULT", {"shieldPowerUpTexture", false, {0.2f,0.2f}, {0,0,0,0}});
    setSpeed({0.f, 0.f});
    //setQuantity(100);
    updateSprite("DEFAULT");
}

void Shield::collision(GameObject *collider) {
    setDestroyed();
}
