//
// Created by Niccolo on 27/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Bullet.h"

Bullet::Bullet(GameObjectType mtype, const std::string &name):
    GameObject(GameObjectGroup::Bullet, mtype, name)
{

}

void Bullet::init(const std::string & texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage) {
    addTexture("DEFAULT", {texture_name, false, scale, {0,0,0,0} });
    updateSprite("DEFAULT");

    m_speed = speed;
    m_damage = damage;
}

int Bullet::getDamage() const {
    return m_damage;
}


