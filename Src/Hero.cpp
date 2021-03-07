//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "InputManager.h"
#include "Hero.h"
#include "Enemy.h"

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

    m_health = hp;
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
        sf::Rect<float> intesrect /* = clacolare il rettangolo di intersezione */;
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
     * Collisione con una piattaforma
     */
    else if(collider->getGroup() == GameObjectGroup::Enemy)
    {
        auto * enemy = dynamic_cast<Enemy *>(collider);
        int damage = enemy->getDamage();
        m_health -= damage;
    }
}

void Hero::speedCap() {
    if(m_speed.y > m_fallingSpeedLimit)
        m_speed.y = m_fallingSpeedLimit;
    else if(m_speed.y < m_jumpSpeedLimit)
        m_speed.y = m_jumpSpeedLimit;
}

bool Hero::gameOver() {
    if (m_health <= 0)
        m_state = State::Dead;
    return m_state == State::Dead;
}


/**/


int Hero::getKnives() const {
    return m_knives;
}

void Hero::setHealth(int hp) {
    Hero::m_health = hp;
    if(Hero::m_health >= getMaxhp()){
        Hero::m_health = getMaxhp();
    }
}

int Hero::getHealth() const {
    return m_health;
}

int Hero::getMaxhp() const {
    return m_maxhp;
}

