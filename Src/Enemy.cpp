//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Enemy.h"

Enemy::Enemy(GameObjectType mtype, const std::string & name) :
    GameObject(GameObjectGroup::Enemy, mtype, name, m_sprite)
{

}

void Enemy::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage)
{
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
        m_sprite.setOrigin(+m_sprite.getTextureRect().width, 0);
    }
    m_speed = speed;
    m_damage = damage;
}

void Enemy::update(int32_t delta_time) {
    GameObject::update(delta_time);
    if(m_state == State::Dead)
        setDestroyed();
}

void Enemy::collision(GameObject *collider) {
    if(m_state == State::Alive) {
        if(collider->getType() == GameObjectType::Hero) {
            m_state = State::Dying;
            setEnabled(false);
        }
    }
}