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
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(3000));
        setStarted(true);
    }
    if(m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
        auto bl = FACTORY->createBullet(EntityType::FireBullet);
        bl->setPosition(sf::Vector2f (getPosition()) - sf::Vector2f(bl->getBounds().width, 0));
        bl->setSpeed(sf::Vector2f {getSpeed().x - 1000.f, 0.f});
        SCENE->addSpawned(bl);
        playSound("FIREACTION");
        m_shoot_left -= 1;
    }
    Enemy::update(delta_time);
}

