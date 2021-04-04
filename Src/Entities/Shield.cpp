//
// Created by angiolo99 on 29/01/20.
//

#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(EntityType::Shield, id)
{
}

Shield::~Shield() {

}

void Shield::init() {
    setSpeed({0.f, 0.f});
    //setQuantity(100);
}

void Shield::event(GameEvent event, Entity *collider) {
    setDestroyed();
}
