//
// Created by angiolo99 on 23/01/20.
//

#include "Entity.h"
#include "Factory.h"
#include "Game.h"
#include "ResourceManager.h"
#include "GameConfig.h"
#include "SceneManager.h"
#include "GameStats.h"
#include "InputManager.h"
#include "Entities/Enemy.h"
#include "Entities/Obstacle.h"
#include "Entities/Knife.h"
#include "Entities/Weapon.h"
#include "Hero.h"

Hero::Hero() :
        Entity(GameObjectGroup::Hero, GameObjectType::Hero, "Hero")
{

}

void Hero::init()
{
    const std::list<Animation::FrameParams> frames = {
            {1, "playerTexture", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);

    setSpeed(CONFIG.getSceneSpeed());

    update_health(300);
    updateKnives(0);
    m_maxhp = 300;
    m_maxknives = 8;

    addSound("COLLISION", "collisionSound");
    addSound("SHIELD", "shieldSound");
    addSound("SHIELDON", "shieldOn");

    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Key::Space);
    m_inputManager.registerKey(sf::Keyboard::Key::K);
}

void Hero::update(int32_t delta_time) {
    if(!isStarted()) {
        update_health(0);
        updateKnives(0);
        setStarted(true);
    }
    m_inputManager.update();
    updatePhysics(delta_time);
    manageAttack();
    Entity::update(delta_time);

    /**/
    m_distance += getSpeed().x * delta_time / 1000;
    STATS.setInt("DISTANCE", (int)m_distance);
}

void Hero::updatePhysics(int32_t delta_time) {
    /*
     * Fallen
     */
    if(getPosition().y > (CONFIG.getWindowSize().y)) {
        m_state = State::Dead;
    }

    /*
     * Manage jump action
     */
    switch(m_state)
    {
        case State::Grounded:
            if(m_inputManager.isKeyJustPressed(sf::Keyboard::Space)) {
                sf::Vector2f accel = {CONFIG.getHeroJumpForce() * CONFIG.getGravity().x, -CONFIG.getHeroJumpForce() * CONFIG.getGravity().y};
                applyImpulse(accel, delta_time);
                m_jumpTimer.restart();
                m_state = State::Jumping;
            }
            else
                m_state = State::Falling;
            break;
        case State::Jumping:
            if(m_inputManager.isKeyPressed(sf::Keyboard::Space) &&
               m_jumpTimer.getElapsedTime() < sf::milliseconds(CONFIG.getHeroJumpMaxTime())) {
                    sf::Vector2f accel = {CONFIG.getHeroJumpForce() * CONFIG.getGravity().x, -CONFIG.getHeroJumpForce() * CONFIG.getGravity().y};
                    applyImpulse(accel, delta_time);
            }
            else {
                m_state = State:: Falling;
            }
            break;
        case State::Falling:
            break;
        case State::Dead:
            break;
    }
    applyImpulse(CONFIG.getGravity(), delta_time);
    speedCap();
}

void Hero::collision(Entity * collider) {
    /*
     * Collisione con una piattaforma
     */
    if(collider->getType() == GameObjectType::Platform)
    {
        sf::Rect<float> collider_rect = collider->getBounds();
        sf::Rect<float> hero_rect = getBounds();
        sf::Rect<float> intersect /* = clacolare il rettangolo di intersezione */;
        /*if(intersrect.width > intersrect.heght)*/
        sf::Vector2f speed = getSpeed();
        if(speed.y >= 0) {
            m_state = State::Grounded;
            speed.y = 0;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top - hero_rect.height));
        }
        else if (speed.y < 0.f) {
            speed.y -= speed.y;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top + collider_rect.height));
        }
        setSpeed(speed);
        /*}*/
    }

    /*
     * Collisione con un nemico
     */
    else if(collider->getGroup() == GameObjectGroup::Enemy)
    {
        auto * enemy = dynamic_cast<Enemy *>(collider);
        int damage = !m_shield ? enemy->getDamage() : 0;
        update_health(-damage);
        if (m_health <= 0)
            m_state = State::Dead;
        playSound(m_shield ? "SHIELDON" : "COLLISION");
        m_shield = false;
    }

    /*
     * Collisione con un ostacolo
     */
    else if(collider->getGroup() == GameObjectGroup::Map)
    {
        auto * obstacle = dynamic_cast<Obstacle *>(collider);
        int damage = !m_shield ? obstacle->getDamage() : 0;
        update_health(-damage);
        if (m_health <= 0)
            m_state = State::Dead;
        playSound(m_shield ? "SHIELDON" : "COLLISION");
        m_shield = false;
    }

    /*
     * Collisione con un powerup
     */
    else if(collider->getGroup() == GameObjectGroup::Powerup)
    {
        if(collider->getType() == GameObjectType::Weapon) {
            auto * weapon = dynamic_cast<Weapon *>(collider);
            updateKnives(weapon->getQuantity());
        }
        else if(collider->getType() == GameObjectType::Shield) {
            m_shield = true;
        }
    }
    /*
     * Collisione con proiettile nemico
     */
    else if (collider->getGroup() == GameObjectGroup::Bullet)
    {
        auto * bullet = dynamic_cast<Bullet *>(collider);
        int damage = !m_shield ? bullet->getDamage():0;
        update_health(-damage);
        if (m_health <= 0)
            m_state = State::Dead;
        playSound(m_shield ? "SHIELDON" : "COLLISION");
        m_shield = false;
    }
}

void Hero::speedCap() {
    sf::Vector2f speed = getSpeed();
    if(speed.y > CONFIG.getHeroFallSpeedLimit()) {
        speed.y = CONFIG.getHeroFallSpeedLimit();
        setSpeed(speed);
    }
    else if(speed.y < CONFIG.getHeroJumpSpeedLimit()){
        speed.y = CONFIG.getHeroJumpSpeedLimit();
        setSpeed(speed);
    }
}

void Hero::update_health(int delta) {
    m_health += delta;
    STATS.setInt("HEALTH", m_health);
}

void Hero::updateKnives(int delta) {
    m_knives += delta;
    m_knives = (m_knives>m_maxknives) ? m_maxknives : m_knives;
    STATS.setInt("KNIVES", m_knives);
}

void Hero::manageAttack() {
    if (m_knives <= 0){
        return;
    }
    switch(m_state){
        case State::Grounded:
        case State::Jumping:
        case State::Falling:
            if(m_inputManager.isKeyJustPressed(sf::Keyboard::K)){
                auto kf = FACTORY.createBullet(GameObjectType::Knife);
                kf->setPosition(sf::Vector2f(getPosition()) + sf::Vector2f(getBounds().width, 0));
                kf->setSpeed(sf::Vector2f {getSpeed().x + 1000.f, 0.f});
                SCENE.addNewEntity(kf);
                updateKnives(-1);
            }
            break;
        case State::Dead:
            break;
    }
}



