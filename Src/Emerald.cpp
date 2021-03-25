//
// Created by Niccolo on 14/03/2021.
//

#include "Emerald.h"

Emerald::Emerald(const std::string& id) :
    Bullet(GameObjectType::EmeraldBullet, id) {}

void Emerald::init() {
    auto animation = m_animator.createAnimation();
    animation->addFrame("emeraldBlockTexture");
    m_animator.play();
    setSpeed({0.f, 0.f});
    setDamage(150);
}

void Emerald::update(int32_t delta_time) {
    GameObject::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void Emerald::collision(GameObject *collider) {
    GameObject::collision(collider);
    if (collider->getType() == GameObjectType::Hero)
        setDestroyed();
}

