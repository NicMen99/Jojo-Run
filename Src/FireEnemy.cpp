//
// Created by angiolo99 on 29/01/20.
//

#include "GameObject.h"
#include "Game.h"
#include "Factory.h"
#include "GameScene.h"
#include "FireEnemy.h"


FireEnemy::FireEnemy(const std::string& id) :
Enemy(GameObjectType::FireEnemy, id) {

}

void FireEnemy::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "fireEnemy", {0,0,0,0}, {0,0}, {true, false}}
    };
    m_animator.addAnimation("DEFAULT", frames);
    setDamage(90);
    addSound("FIREACTION", "fireEnemyShout");
}

void FireEnemy::update(int32_t delta_time) {
    Enemy::update(delta_time);
    if(!isStarted()) {
        m_shootTimer.restart();
        m_shootTime = sf::milliseconds(RAND(3000));
    }
    if(m_shoot_left > 0 && m_shootTimer.getElapsedTime() >= m_shootTime) {
        auto bl = GF.createBullet(GameObjectType::FireBullet);
        bl->setPosition({getPosition()});
        bl->setSpeed(sf::Vector2f {m_speed.x - 1000.f, 0.f});
        GS.addItem(bl);
        playSound("FIREACTION");
        m_shoot_left -= 1;
    }
    setStarted(true);}

