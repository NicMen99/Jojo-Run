//
// Created by angiolo99 on 29/01/20.
//

#include "Game.h"
#include "HamonEnemy.h"

HamonEnemy::HamonEnemy(const std::string& id) :
    Enemy(EntityType::HamonEnemy, id) {
}

HamonEnemy::~HamonEnemy() {

}

void HamonEnemy::init() {
    setDamage(70);
    setLifeBonus(10);
}

void HamonEnemy::update(int32_t delta_time) {
    if(!isStarted()) {
        changeState(State::Idle);
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(1000)+1000);
        m_shoot_left = RAND(3); // 0 - 2
        setStarted(true);
    }
    if(State::Idle == m_state) {
        if(getPosition().x < CONFIG->getWindowSize().x) {
            if (m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
                applyImpulse({0.f, -CONFIG->getGravity().y*600.f}, 20);
                setDamage(150);
                changeState(State::Attack);
            }
        }
    }
    else if(State::Attack == m_state) {
        if (animationCompleted()) {
            m_shoot_left--;
            m_shootTimer.restart();
            m_shootTime = sf::milliseconds(RAND(1000) + 500);
            setDamage(70);
            changeState(State::Idle);
        }
    }
    Enemy::update(delta_time);
}

void HamonEnemy::changeState(Enemy::State new_state) {
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
