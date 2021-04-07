//
// Created by angiolo99 on 23/01/20.
//

#include <iostream>

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
    m_health = 300;
    m_knives = 0;
    m_maxhealthpoints = 300;
    m_maxknives = 8;
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Key::Space);
    m_inputManager.registerKey(sf::Keyboard::Key::K);
}

void Hero::update(int32_t delta_time) {
    if(!isStarted()) {
        updateHealth(0);
        updateKnives(2);
        setStarted(true);
        m_distance = 0;
        m_clean_distance = 0;
    }
    m_inputManager.update();
    updatePhysics(delta_time);
    manageAttack();
    Entity::update(delta_time);
    /**/
    m_distance += getSpeed().x * delta_time / 1000;
    m_clean_distance += getSpeed().x * delta_time / 1000;
    STATS->setInt(Stats::Distance, (int)m_distance);
    STATS->setInt(Stats::CleanDistance, (int)m_clean_distance);
}

void Hero::updatePhysics(int32_t delta_time) {
    /*
     * Fallen
     */
    if(getPosition().y > (CONFIG->getWindowSize().y)) {
        m_state = State::Dead;
        setEnabled(false);
        setDestroyed();
    }

    /*
     * Manage jump action
     */
    switch(m_state)
    {
        case State::Grounded:
            if(m_inputManager.isKeyJustPressed(sf::Keyboard::Space)) {
                sf::Vector2f accel = {0, -CONFIG->getHeroJumpForce() + CONFIG->getGravity().y};
                applyImpulse(accel, delta_time);
                m_jumpTimer.restart();
                changeState(State::Jumping);
            }
            if(getSpeed().y > 250.f) {
                changeState(State::Falling);
            }
            break;
        case State::Jumping:
            if(m_inputManager.isKeyPressed(sf::Keyboard::Space) &&
               m_jumpTimer.getElapsedTime() < sf::milliseconds(CONFIG->getHeroJumpMaxTime())) {
                    sf::Vector2f accel = {0, -CONFIG->getHeroJumpForce() + CONFIG->getGravity().y};
                    applyImpulse(accel, delta_time);
            }
            else {
                if(getSpeed().y>=0) {
                    changeState(State::Falling);
                }
            }
            break;
        case State::Falling:
            break;
        case State::Dead:
            break;
        case State::Init:
            break;
    }
    applyImpulse(CONFIG->getGravity(), delta_time);
    speedCap();
}

void Hero::event(GameEvent event, Entity * entity) {

    if (event == GameEvent::CollisionBottom) {
        /*
         * Atterraggio su piattaforma
         */
        if (entity->getGroup() == EntityGroup::Platform) {
            sf::Rect<float> collider_rect = entity->getBounds();
            sf::Rect<float> hero_rect = getBounds();
            sf::Vector2f speed = getSpeed();
            if(m_state==State::Falling || m_state==State::Init)
                changeState(State::Grounded);
            speed.y = 0;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top - hero_rect.height));
            setSpeed(speed);
        }
    }

    else if(event == GameEvent::CollisionTop) {
        /*
         * impatto con piattaforma
         */
        if (entity->getGroup() == EntityGroup::Platform) {
            sf::Rect<float> collider_rect = entity->getBounds();
            sf::Rect<float> hero_rect = getBounds();
            sf::Vector2f speed = getSpeed();
            speed.y -= speed.y;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top + collider_rect.height));
            setSpeed(speed);
        }
    }

    else if(event == GameEvent::Collision) {
        /*
         * Collisione con un nemico
         */
        int damage = 0;
        if (entity->getGroup() == EntityGroup::Enemy) {
            auto *enemy = dynamic_cast<Enemy *>(entity);
            damage = enemy->getDamage();
            if(State::Falling == m_state) {
                damage /= 3;
                setSpeed(getSpeed().x, -getSpeed().y/2);
            }
            else {
                applyImpulse({0, -CONFIG->getHeroJumpForce()/40}, 10);
            }
        }
        /*
         * Collisione con un ostacolo
         */
        else if (entity->getGroup() == EntityGroup::Obstacle) {
            auto *obstacle = dynamic_cast<Obstacle *>(entity);
            damage = obstacle->getDamage();
        }
        /*
         * Collisione con proiettile nemico
         */
        else if (entity->getGroup() == EntityGroup::Bullet) {
            #ifdef GAMEDEBUG
            assert(entity->getType() != EntityType::Knife);
            #endif
            auto *bullet = dynamic_cast<Bullet *>(entity);
            damage = bullet->getDamage();
            if(!m_shield)
                applyImpulse({0, -CONFIG->getHeroJumpForce()/50}, 10);
        }
        else
            return;

        playSound("COLLISION");
        if(m_shield) {
            if(m_state==State::Grounded) {
                playAnimation("RUN", true);
            }
            m_shield = false;
        }
        else {
            if(damage>0)
                m_clean_distance = 0;
            updateHealth(-damage);
            if (m_health <= 0) {
                applyImpulse({-CONFIG->getGravity().y*10, -CONFIG->getHeroJumpForce()}, 10);
                changeState(State::Dead);
            }
        }
    }

    else if(event == GameEvent::Collection) {
        /*
         * Potenziamento raccolto
         */
        if (entity->getGroup() == EntityGroup::Powerup) {
            if (entity->getType() == EntityType::Weapon) {
                auto *weapon = dynamic_cast<Weapon *>(entity);
                updateKnives(weapon->getQuantity());
            } else if (entity->getType() == EntityType::Shield) {
                if(m_state==State::Grounded) {
                    playAnimation("SRUN", true);
                    playSound("SHIELDON");
                }
                m_shield = true;
            }
        }
    }

    else if (event == GameEvent::EnemyKilled) {
        /*
         * Nemico ucciso con proiettile
         */
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
    if(m_health < 0)
        m_health = 0;
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
                /* I frame sono a larghezza variabile, posizione di spawn un frame avanti */
                kf->setPosition(sf::Vector2f(getPosition()) + sf::Vector2f(getBounds().width * 2, 0));
                kf->setSpeed(sf::Vector2f {getSpeed().x + CONFIG->getKnifeSpeed(), 0.f});
                SCENE->addSpawned(kf);
                updateKnives(-1);
            }
            break;
        case State::Dead:
        case State::Init:
            break;
    }
}

void Hero::changeState(State new_state) {
    if(new_state != m_state) {
        switch(new_state) {
            case State::Grounded:
// std::cout << "RUN" << std::endl;
                if(!m_shield) {
                    playAnimation("RUN", true);
                }
                else {
                    playAnimation("SRUN", true);
                }
                break;
            case State::Jumping:
// std::cout << "JUMP" << std::endl;
                playAnimation("JUMP");
                break;
            case State::Falling:
// std::cout << "FALL" << std::endl;
                playAnimation("FALL");
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



