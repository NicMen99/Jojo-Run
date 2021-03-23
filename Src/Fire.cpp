//
// Created by Niccolo on 14/03/2021.
//

#include "Fire.h"

Fire::Fire(std::string id) :
    Bullet(GameObjectType::FireBullet, id) {

}

void Fire::init() {
    addTexture("DEFAULT", {"fireBlockTexture", {0,0 }});
    setSpeed({0.f, 0.f});
    setDamage(50);
    updateSprite("DEFAULT");
}

void Fire::update(int32_t delta_time) {
    GameObject::update(delta_time);
    if(getPosition().x < 0)
        setDestroyed();
}

void Fire::collision(GameObject *collider) {
    GameObject::collision(collider);
    if (collider->getType() == GameObjectType::Hero)
        setDestroyed();
}
