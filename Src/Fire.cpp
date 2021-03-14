//
// Created by Niccolo on 14/03/2021.
//

#include "Fire.h"

Fire::Fire(std::string id) :
    Bullet(GameObjectType::FireBullet, id) {

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
