//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "GameStats.h"
#include "InputManager.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Weapon.h"
#include "Shield.h"
#include "Hero.h"

Hero::Hero() :
    GameObject(GameObjectGroup::Hero, GameObjectType::Hero, "Hero", m_sprite)
{

}

void Hero::init()
{
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Key::Space);
    m_inputManager.registerKey(sf::Keyboard::Key::K);
    init("playerTexture");
    setPosition(sf::Vector2f(200.f,GC.getMBase()));
}

void Hero::update(int32_t delta_time) {
    if(!isStarted()) {
        update_health(0);
        setStarted(true);
    }
    m_inputManager.update();
    updatePhysics(delta_time);
    GameObject::update(delta_time);
}

void Hero::init(const std::string &texture_name, int hp, int knives, int max_kinves, int max_health) {
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        setTexture(*texture);
    }
    m_speed = GC.getSceneSpeed();

    update_health(hp);
    m_knives = knives;
    m_maxhp = max_health;
    m_maxknives = max_kinves;

    sf::SoundBuffer* soundBuffer = RM.getSound("collisionSound");
    if(soundBuffer != nullptr) {
        m_collisionSound.setBuffer(*soundBuffer);
        m_collisionSound.setVolume(22.f);
    }
    soundBuffer = RM.getSound("shieldSound");
    if(soundBuffer != nullptr) {
        m_powerUpSound.setBuffer(*soundBuffer);
        m_powerUpSound.setVolume(22.f);
    }
    soundBuffer = RM.getSound("shieldOn");
    if(soundBuffer != nullptr) {
        m_shieldOnSound.setBuffer(*soundBuffer);
        m_shieldOnSound.setVolume(22.f);
    }
}

void Hero::setTexture(const sf::Texture &heroTexture){
    m_sprite.setTexture(heroTexture);
    m_sprite.setScale(0.9, 0.9);
}

void Hero::updatePhysics(int32_t delta_time) {

    /*
     * Fallen
     */
    if(getPosition().y > (GC.getWindowSize().y)) {
        m_state = State::Dead;
    }

    /*
     * Manage jump action
     */
    switch(m_state)
    {
        case State::Grounded:
            if(m_inputManager.isKeyJustPressed(sf::Keyboard::Space)) {
                sf::Vector2f accel = {m_initialJumpForce * GC.getGravity().x, -m_initialJumpForce * GC.getGravity().y};
                applyImpulse(accel, delta_time);
                m_jumpTimer.restart();
                m_state = State::Jumping;
            }
            else
                m_state = State::Falling;
            break;
        case State::Jumping:
            if(m_inputManager.isKeyPressed(sf::Keyboard::Space) &&
               m_jumpTimer.getElapsedTime() < m_maxJumpTime) {
                    sf::Vector2f accel = {m_jumpForce * GC.getGravity().x, -m_jumpForce * GC.getGravity().y};
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
    applyImpulse(GC.getGravity(), delta_time);
    speedCap();
}

void Hero::collision(GameObject * collider)
{
    /*
     * Collisione con una piattaforma
     */
    if(collider->getType() == GameObjectType::Platform)
    {
        sf::Rect<float> collider_rect = collider->getBounds();
        sf::Rect<float> hero_rect = getBounds();
        sf::Rect<float> intesrect  /* = clacolare il rettangolo di intersezione */;
        /*if(intersrect.width > intersrect.heght)*/
        if(m_speed.y >= 0) {
            m_state = State::Grounded;
            m_speed.y = 0;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top - hero_rect.height));
        }
        else if (m_speed.y <= 0.f) {
            m_speed.y -= m_speed.y;
            setPosition(sf::Vector2f(hero_rect.left, collider_rect.top + collider_rect.height));
        }
        /*}*/
    }

    /*
     * Collisione con un nemico
     */
    else if(collider->getGroup() == GameObjectGroup::Enemy)
    {
        auto * enemy = dynamic_cast<Enemy *>(collider);
        if(!m_shield) {
            int damage = enemy->getDamage();
            update_health(-damage);
            if (m_health <= 0)
                m_state = State::Dead;
        }
        m_shield = false;
    }

    /*
     * Collisione con un ostacolo
     */
    else if(collider->getGroup() == GameObjectGroup::Map)
    {
        auto * obstacle = dynamic_cast<Obstacle *>(collider);
        int damage = obstacle->getDamage();
        update_health(-damage);
        if (m_health <= 0)
            m_state = State::Dead;
    }

    /*
     * Collisione con un powerup
     */
    else if(collider->getGroup() == GameObjectGroup::Powerup)
    {
        if(collider->getType() == GameObjectType::Weapon) {
            auto * weapon = dynamic_cast<Weapon *>(collider);
            m_knives += weapon->collect();
            m_knives = (m_knives>m_maxknives) ? m_maxknives : m_knives;
        }
        else if(collider->getType() == GameObjectType::Shield) {
            m_shield = true;
        }
    }

}

void Hero::speedCap() {
    if(m_speed.y > m_fallingSpeedLimit)
        m_speed.y = m_fallingSpeedLimit;
    else if(m_speed.y < m_jumpSpeedLimit)
        m_speed.y = m_jumpSpeedLimit;
}

bool Hero::gameOver() {
    return m_state == State::Dead;
}

void Hero::update_health(int delta) {
    m_health += delta;
    STATS.setInt("HEALTH", m_health);
}


