//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "Enemy.h"

Enemy::Enemy(EntityType mtype, const std::string & name) :
        Entity(EntityGroup::Enemy, mtype, name) {

}

Enemy::~Enemy() {

}

void Enemy::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage)
{
}

void Enemy::update(int32_t delta_time) {
    updatePhysics(delta_time);
    Entity::update(delta_time);
}

void Enemy::event(GameEvent event, Entity *collider) {
    /*
     * Platform collision
     */
    if (event == GameEvent::CollisionBottom) {
        sf::Rect<float> collider_rect = collider->getBounds();
        sf::Rect<float> enemy_rect = getBounds();
        sf::Vector2f speed = getSpeed();
        speed.y = 0;
        setPosition(sf::Vector2f(enemy_rect.left, collider_rect.top - enemy_rect.height));
        setSpeed(speed);
    }
    else if (event == GameEvent::Collision) {
        if(collider->getType() == EntityType::Hero) {
            m_state = State::Dead;
            STATS->addInt(Stats::Killed, 1);
            STATS->setInt(Stats::ConsecutiveKilled, 0);
            applyImpulse({CONFIG->getGravity().y*50, -CONFIG->getEnemyJumpForce()}, 10);
            setEnabled(false);
        }
        if (collider->getType() == EntityType::Knife) {
            m_state = State::Dead;
            STATS->addInt(Stats::Killed, 1);
            STATS->addInt(Stats::ConsecutiveKilled, 1);
            applyImpulse({CONFIG->getGravity().y*10, -CONFIG->getEnemyJumpForce()}, 10);
            setEnabled(false);
        }
    }
    else if (event == GameEvent::OutOfBound) {
        STATS->setInt(Stats::ConsecutiveKilled, 0);
    }
}

void Enemy::updatePhysics(int32_t delta_time) {
    /*
     * Fallen
     */
    if(getPosition().y > (CONFIG->getWindowSize().y)) {
        m_state = State::Dead;
        setEnabled(false);
        setDestroyed();
    }
    applyImpulse(CONFIG->getGravity(), delta_time);
    speedCap();
}

void Enemy::speedCap() {
    sf::Vector2f speed = getSpeed();
    if(speed.y > CONFIG->getEnemyFallSpeedLimit()) {
        speed.y = CONFIG->getEnemyFallSpeedLimit();
        setSpeed(speed);
    }
    else if(speed.y < CONFIG->getEnemyJumpSpeedLimit()){
        speed.y = CONFIG->getEnemyJumpSpeedLimit();
        setSpeed(speed);
    }
}
