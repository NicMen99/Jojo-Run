//
// Created by angiolo99 on 29/01/20.
//

#include "Entity.h"
#include "Game.h"
#include "Factory.h"
#include "SceneManager.h"
#include "EmeraldEnemy.h"

EmeraldEnemy::EmeraldEnemy(const std::string& id) :
    Enemy(GameObjectType::EmeraldEnemy, id)
{

}

void EmeraldEnemy::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "emeraldEnemyTexture", {0,0,0,0}, {0,0}, {true, false}}
    };
    addAnimation("DEFAULT", frames);
    setDamage(90);
    setLifeBonus(20);
    addSound("EMERALDACTION", "emeraldEnemyShout");
}

void EmeraldEnemy::update(int32_t delta_time) {
    Enemy::update(delta_time);
    if(!isStarted()) {
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(3000));
        setStarted(true);
    }
    if(m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
        auto bl = FACTORY.createBullet(GameObjectType::EmeraldBullet);
        bl->setPosition({getPosition()});
        bl->setSpeed(sf::Vector2f {bl->getSpeed().x - 1000.f, 0.f});
        SCENE.addNewEntity(bl);
        playSound("EMERALDACTION");
        m_shoot_left -= 1;
    }
}

