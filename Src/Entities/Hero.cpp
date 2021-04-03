//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "Entity.h"
#include "Entities/Enemy.h"
#include "Entities/Obstacle.h"
#include "Entities/Knife.h"
#include "Entities/Weapon.h"
#include "AnimationManager.h"

#include "Hero.h"

Hero::Hero() :
        Entity(EntityGroup::Hero, EntityType::Hero, "Hero")
{

}

Hero::~Hero() {

}

void Hero::init()
{
    setSpeed(CONFIG->getSceneSpeed());
    updateHealth(300);
    updateKnives(0);
    m_maxhealthpoints = 300;
    m_maxknives = 8;
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Key::Space);
    m_inputManager.registerKey(sf::Keyboard::Key::K);
}

void Hero::update(int32_t delta_time) {
    if(!isStarted()) {
        updateHealth(0);
        updateKnives(0);
    }
    m_inputManager.update();
    updatePhysics(delta_time);
    manageAttack();
    Entity::update(delta_time);

    /**/
    m_distance += getSpeed().x * delta_time / 1000;
    STATS->setInt(Stats::Distance, (int)m_distance);
}

void Hero::updatePhysics(int32_t delta_time) {
    /*
     * Fallen
     */
    if(getPosition().y > (CONFIG->getWindowSize().y)) {
        m_state = State::Dead;
    }

    /*
     * Manage jump action
     */
    switch(m_state)
    {
        case State::Grounded:
            if(m_inputManager.isKeyJustPressed(sf::Keyboard::Space)) {
                sf::Vector2f accel = {CONFIG->getHeroJumpForce() * CONFIG->getGravity().x, -CONFIG->getHeroJumpForce() * CONFIG->getGravity().y};
                applyImpulse(accel, delta_time);
                m_jumpTimer.restart();
                m_state = State::Jumping;
            }
            else
                m_state = State::Falling;
            break;
        case State::Jumping:
            if(m_inputManager.isKeyPressed(sf::Keyboard::Space) &&
               m_jumpTimer.getElapsedTime() < sf::milliseconds(CONFIG->getHeroJumpMaxTime())) {
                    sf::Vector2f accel = {CONFIG->getHeroJumpForce() * CONFIG->getGravity().x, -CONFIG->getHeroJumpForce() * CONFIG->getGravity().y};
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
    applyImpulse(CONFIG->getGravity(), delta_time);
    speedCap();
}

void Hero::event(GameEvent event, Entity * entity) {
    if(event == GameEvent::Collision) {

        /*
         * Collisione con una piattaforma
         */
        if (entity->getGroup() == EntityGroup::Platform) {
            sf::Rect<float> collider_rect = entity->getBounds();
            sf::Rect<float> hero_rect = getBounds();
            sf::Vector2f speed = getSpeed();
            if (speed.y >= 0) {
                m_state = State::Grounded;
                speed.y = 0;
                setPosition(sf::Vector2f(hero_rect.left, collider_rect.top - hero_rect.height));
            } else if (speed.y < 0.f) {
                speed.y -= speed.y;
                setPosition(sf::Vector2f(hero_rect.left, collider_rect.top + collider_rect.height));
            }
            setSpeed(speed);
            /*}*/
        }

            /*
             * Collisione con un nemico
             */
        else if (entity->getGroup() == EntityGroup::Enemy) {
            auto *enemy = dynamic_cast<Enemy *>(entity);
            int damage = !m_shield ? enemy->getDamage() : 0;
            updateHealth(-damage);
            if (m_health <= 0)
                m_state = State::Dead;
            playSound(m_shield ? "SHIELDON" : "COLLISION");
            m_shield = false;
        }

            /*
             * Collisione con un ostacolo
             */
        else if (entity->getGroup() == EntityGroup::Obstacle) {
            auto *obstacle = dynamic_cast<Obstacle *>(entity);
            int damage = !m_shield ? obstacle->getDamage() : 0;
            updateHealth(-damage);
            if (m_health <= 0)
                m_state = State::Dead;
            playSound(m_shield ? "SHIELDON" : "COLLISION");
            m_shield = false;
        }

            /*
             * Collisione con un powerup
             */
        else if (entity->getGroup() == EntityGroup::Powerup) {
            if (entity->getType() == EntityType::Weapon) {
                auto *weapon = dynamic_cast<Weapon *>(entity);
                updateKnives(weapon->getQuantity());
            } else if (entity->getType() == EntityType::Shield) {
                m_shield = true;
            }
        }
            /*
             * Collisione con proiettile nemico
             */
        else if (entity->getGroup() == EntityGroup::Bullet) {
            auto *bullet = dynamic_cast<Bullet *>(entity);
            int damage = !m_shield ? bullet->getDamage() : 0;
            updateHealth(-damage);
            if (m_health <= 0)
                m_state = State::Dead;
            playSound(m_shield ? "SHIELDON" : "COLLISION");
            m_shield = false;
        }
    }
    else if (event == GameEvent::EnemyKilled) {
        if(entity->getGroup() == EntityGroup::Enemy) {
            auto * enemy = dynamic_cast<Enemy*>(entity);
            updateHealth(enemy->getLifeBonus());
        }
    }
}

void Hero::speedCap() {
    sf::Vector2f speed = getSpeed();
    if(speed.y > CONFIG->getHeroFallSpeedLimit()) {
        speed.y = CONFIG->getHeroFallSpeedLimit();
        setSpeed(speed);
    }
    else if(speed.y < CONFIG->getHeroJumpSpeedLimit()){
        speed.y = CONFIG->getHeroJumpSpeedLimit();
        setSpeed(speed);
    }
}

void Hero::updateHealth(int delta) {
    m_health += delta;
    if(m_health > m_maxhealthpoints) {
        m_health = m_maxhealthpoints;
    }
    STATS->setInt(Stats::Health, m_health);
}

void Hero::updateKnives(int delta) {
    m_knives += delta;
    m_knives = (m_knives>m_maxknives) ? m_maxknives : m_knives;
    STATS->setInt(Stats::Knives, m_knives);
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
                auto kf = FACTORY->createBullet(EntityType::Knife);
                kf->setPosition(sf::Vector2f(getPosition()) + sf::Vector2f(getBounds().width, 0));
                kf->setSpeed(sf::Vector2f {getSpeed().x + 1000.f, 0.f});
                SCENE->addSpawned(kf);
                updateKnives(-1);
            }
            break;
        case State::Dead:
            break;
    }
}




