//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "ResourceManager.h"
#include "GameStats.h"
#include "Enemy.h"

Enemy::Enemy(GameObjectType mtype, const std::string & name) :
        Entity(GameObjectGroup::Enemy, mtype, name) {

}

void Enemy::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage)
{
}

void Enemy::update(int32_t delta_time) {
    Entity::update(delta_time);
    if(m_state == State::Dying) {
        setEnabled(false);
        if(m_dyingTimer.getElapsedTime() > sf::milliseconds(100))
            m_state = State::Dead;
    }
    else if(m_state == State::Dead)
        setDestroyed();
}

void Enemy::event(GameEvent event, Entity *collider) {
    if(m_state == State::Alive) {
        if(collider->getType() == GameObjectType::Hero) {
            m_state = State::Dying;
            m_dyingTimer.restart();
            STATS.setInt(Stats::ConsecutiveKilled, 0);
        }
        if (collider->getType() == GameObjectType::Knife) {
            m_state = State::Dead;
            m_dyingTimer.restart();
            STATS.addInt(Stats::Killed, 1);
            STATS.addInt(Stats::ConsecutiveKilled, 1);
        }
    }
}
