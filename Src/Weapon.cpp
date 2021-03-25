//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(GameObjectType::Weapon, "Weapons")
{

}

void Weapon::init() {
    auto animation = m_animator.createAnimation();
    animation->addFrame("knifeTexture");
    m_animator.play();
    setSpeed({0.f, 0.f});
    setQuantity(2);
}

void Weapon::collision(GameObject *collider) {
    setDestroyed();
}
