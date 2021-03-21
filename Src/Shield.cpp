//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(GameObjectType::Shield, id)
{
}

void Shield::init() {
    addTexture("DEFAULT", {"shieldPowerUpTexture", {39, 77}, false, false});
    setSpeed({0.f, 0.f});
    //setQuantity(100);
    updateSprite("DEFAULT");
}

void Shield::collision(GameObject *collider) {
    setDestroyed();
}
