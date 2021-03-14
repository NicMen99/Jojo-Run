//
// Created by angiolo99 on 29/01/20.
//

#include "GameObject.h"
#include "Game.h"
#include "Factory.h"
#include "GameScene.h"
#include "Knife.h"
#include "EmeraldEnemy.h"

EmeraldEnemy::EmeraldEnemy(const std::string& id) :
    Enemy(GameObjectType::EmeraldEnemy, id)
{

}

std::unique_ptr<Bullet> EmeraldEnemy::SpecialAction() {
    std::unique_ptr<Bullet> bullet = std::unique_ptr<Bullet>(new Knife(""));
    bullet->init("emeraldBlockTexture", {1, 0}, {0.25, 0.25}, 100);
    return bullet;
}

void EmeraldEnemy::update(int32_t delta_time) {
    Enemy::update(delta_time);
    if(!isStarted()) {
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(4000));
    }
    if(m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
        /*
        auto bl = GF.createBullet(BulletType::EmeraldBullet);
        bl->setPosition({getPosition()});
        bl->setSpeed(sf::Vector2f {m_speed.x - 1000.f, 0.f});
        GS.addItem(bl);
        m_shoot_left -= 1;
         */
    }
    setStarted(true);
}

