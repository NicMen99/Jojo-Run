//
// Created by Niccolo on 14/03/2021.
//

#include "FireBall.h"

FireBall::FireBall(std::string id) :
    Bullet(GameObjectType::FireBullet, id) {

}

void FireBall::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "fireBlockTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    m_animator.addAnimation("DEFAULT", frames);
    setSpeed({0.f, 0.f});
    setDamage(50);
}

void FireBall::update(int32_t delta_time) {
    GameObject::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void FireBall::collision(GameObject *collider) {
    GameObject::collision(collider);
    if (collider->getType() == GameObjectType::Hero)
        setDestroyed();
}
