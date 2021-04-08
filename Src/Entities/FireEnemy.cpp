//
// Created by angiolo99 on 29/01/20.
//

#include "Entity.h"
#include "Game.h"
#include "FireEnemy.h"


FireEnemy::FireEnemy(const std::string& id) :
Enemy(EntityType::FireEnemy, id) {

}

FireEnemy::~FireEnemy() {

}

void FireEnemy::init() {
    setDamage(90);
    setLifeBonus(30);
}

void FireEnemy::update(int32_t delta_time) {
    if(!isStarted()) {
        changeState(State::Idle);
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(1000)+1000);
        m_shoot_left = RAND(4); // 0 - 3
        setStarted(true);
    }
    if(State::Idle == m_state) {
        if(getPosition().x < CONFIG->getWindowSize().x) {
            if (m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
                changeState(State::Attack);
            }
        }
    }
    else if(State::Attack == m_state) {
        if (animationCompleted()) {
            auto bl = FACTORY->createBullet(EntityType::FireBullet);
            bl->setPosition(sf::Vector2f (getPosition()) - sf::Vector2f(bl->getBounds().width/2, 0));
            bl->setSpeed(sf::Vector2f {getSpeed().x - CONFIG->getFireBulletSpeed(), 0.f});
            SCENE->addSpawned(bl);
            m_shoot_left--;
            m_shootTimer.restart();
            m_shootTime = sf::milliseconds(100);
            changeState(State::Idle);
        }
    }
    Enemy::update(delta_time);
}

void FireEnemy::changeState(Enemy::State new_state) {
    if(new_state != m_state) {
        switch(new_state) {
            case State::Idle:
                playAnimation("IDLE");
                break;
            case State::Attack:
                playAnimation("ATTACK");
                playSound("ATTACK");
                break;
            case State::Dead:
                playAnimation("DEATH");
                playSound("DEATH");
                setEnabled(false);
                break;
            default:
                break;
        }
    }
    m_state = new_state;
}
