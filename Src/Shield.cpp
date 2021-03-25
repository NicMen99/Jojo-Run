//
// Created by angiolo99 on 29/01/20.
//
#include "Shield.h"

Shield::Shield(std::string id) :
    PowerUp(GameObjectType::Shield, id)
{
}

void Shield::init() {
    auto animation = m_animator.createAnimation();
    animation->addFrame("shieldPowerUpTexture", {0,0,0,0}, 1, {39,77}, true, false);
    m_animator.play();
    setSpeed({0.f, 0.f});
    //setQuantity(100);
}

void Shield::collision(GameObject *collider) {
    setDestroyed();
}
