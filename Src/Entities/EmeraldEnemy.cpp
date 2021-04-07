//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "Entity.h"
#include "EmeraldEnemy.h"

EmeraldEnemy::EmeraldEnemy(const std::string& id) :
    Enemy(EntityType::EmeraldEnemy, id)
{

}

EmeraldEnemy::~EmeraldEnemy(){

}

void EmeraldEnemy::init() {
    setDamage(90);
    setLifeBonus(20);
}

void EmeraldEnemy::update(int32_t delta_time) {
    if(!isStarted()) {
        changeState(State::Idle);
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(1000)+1000);
        m_shoot_left = RAND(2); // 0 - 1
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
            auto bl = FACTORY->createBullet(EntityType::EmeraldBullet);
            bl->setPosition(sf::Vector2f (getPosition()) - sf::Vector2f(bl->getBounds().width/2, 0));
            bl->setSpeed(sf::Vector2f {getSpeed().x - CONFIG->getEmeraldBulletSpeed(), 0.f});
            SCENE->addSpawned(bl);
            playSound("EMERALDACTION");
            m_shoot_left--;
            m_shootTimer.restart();
            m_shootTime = sf::milliseconds(100);
            changeState(State::Idle);
        }
    }
    Enemy::update(delta_time);
}

void EmeraldEnemy::changeState(Enemy::State new_state) {
    if(new_state != m_state) {
        switch(new_state) {
            case State::Idle:
                playAnimation("IDLE");
                break;
            case State::Attack:
                playAnimation("ATTACK");
                break;
            case State::Dead:
                playAnimation("DEATH");
                setEnabled(false);
                break;
            default:
                break;
        }
    }
    m_state = new_state;
}



