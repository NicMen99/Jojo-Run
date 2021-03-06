//
// Created by Niccolo on 27/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Bullet.h"

Bullet::Bullet(GameObjectType mtype, const std::string &name):
    GameObject(GameObjectGroup::Bullet, mtype, name, m_sprite)
{

}

void Bullet::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage) {
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
    m_damage = damage;
}

