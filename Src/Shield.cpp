//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(GameObjectType::Shield, id)
{
}

void Shield::collision(GameObject *collider) {
    setDestroyed();
}
