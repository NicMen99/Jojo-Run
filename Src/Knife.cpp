//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "GameConfig.h"
#include "Knife.h"

Knife::Knife(std::string id) :
    Bullet(GameObjectType::Knife, id)
{
}

void Knife::update(int32_t delta_time) {
    GameObject::update(delta_time);
    if(getPosition().x > GC.getWindowSize().x)
        setDestroyed();
}

void Knife::collision(GameObject *collider) {
    GameObject::collision(collider);
    setDestroyed();
}





