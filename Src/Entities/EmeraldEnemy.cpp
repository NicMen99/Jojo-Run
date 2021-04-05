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
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(3000));
        setStarted(true);
    }
    if(m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
        auto bl = FACTORY->createBullet(EntityType::EmeraldBullet);
        bl->setPosition(sf::Vector2f (getPosition()) - sf::Vector2f(bl->getBounds().width, 0)   );
        bl->setSpeed(sf::Vector2f {bl->getSpeed().x - 1000.f, 0.f});
        SCENE->addSpawned(bl);
        playSound("EMERALDACTION");
        m_shoot_left -= 1;
    }
    Enemy::update(delta_time);
}



