//
// Created by Niccolo on 28/02/2021.
//

#include "Weapon.h"

Weapon::Weapon(std::string id) :
    PowerUp(GameObjectType::Weapon, "Weapons")
{

}

void Weapon::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "knifeTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    m_animator.addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setQuantity(2);
}

void Weapon::collision(Entity *collider) {
    setDestroyed();
}
