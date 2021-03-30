//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(GameObjectType::Shield, id)
{
}

Shield::~Shield() {

}

void Shield::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "shieldPowerUpTexture", {0,0,0,0}, {39,77}, {true, false}}
    };
    addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    //setQuantity(100);
}

void Shield::event(GameEvent event, Entity *collider) {
    setDestroyed();
}
