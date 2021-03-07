//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "InputManager.h"
#include "Hero.h"

Hero::Hero() :
    GameObject(GameObjectGroup::Hero, GameObjectType::Hero, "Hero", m_sprite)
{

}

void Hero::init()
{
    HERO.init("playerTexture");
    HERO.setPosition(sf::Vector2f(65.f,0.f));
}

void Hero::update(int32_t delta_time) {
    processInput(delta_time);
    updatephysics(delta_time);
}

void Hero::init(const std::string &texture_name, int hp, int knives, int max_kinves, int max_health) {
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        setTexture(*texture);
    }
    m_speed = GC.getSceneSpeed();

    m_hp = hp;
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

void Hero::processInput(int32_t delta_time) {
    if(m_grounded) {
        if(IM.isKeyJustPressed(sf::Keyboard::Space))
            jumpAction(delta_time);
    }
}

void Hero::updatephysics(int32_t delta_time) {
    if(!m_grounded) {
        m_speed += sf::Vector2f(0, GC.gravity() * delta_time);
    }
    GameObject::update(delta_time);
    /*
     * Normalizza la posizione @TODO levare costante
     */
    sf::Vector2f pos = getPosition();
    if(pos.y > (GC.getWindowSize().y - 100.f)) {
        pos.y = GC.getWindowSize().y - 100.f;
        setPosition(pos);
        m_speed.y = 0;
        m_grounded = true;
    }
}

void Hero::jumpAction(int32_t delta_time) {
    /*
     * @TODO cambiare costanti
     */
    m_speed -= sf::Vector2f(0, 1100.f);
    m_grounded = false;
}



bool Hero::gameOver() {
    if (m_hp <= 0)
        death();
    return m_isDead;
}


sf::Vector2f Hero::getHeroSize() const {
    float x = m_sprite.getGlobalBounds().width;
    float y = m_sprite.getGlobalBounds().height;
    return sf::Vector2f{x, y};
}

void Hero::setKnives(int knives) {
    Hero::m_knives = knives;
    if(Hero::m_knives >= getMaxknives()){
        Hero::m_knives = getMaxknives();
    }
}


int Hero::getKnives() const {
    return m_knives;
}

void Hero::setHealth(int hp) {
    Hero::m_hp = hp;
    if(Hero::m_hp >= getMaxhp()){
        Hero::m_hp = getMaxhp();
    }
}

int Hero::getHealth() const {
    return m_hp;
}

int Hero::getMaxknives() const {
    return m_maxknives;
}

void Hero::setMaxknives(int maxknives) {
    Hero::m_maxknives = maxknives;
}

int Hero::getMaxhp() const {
    return m_maxhp;
}

void Hero::setMaxhp(int maxhp) {
    Hero::m_maxhp = maxhp;
}

void Hero::setShieldOn() {
    if(!m_shield) {
        sf::Texture* texture = RM.getTexture("playerShieldTexture");
        if(texture != nullptr){
            texture->setSmooth(true);
            setTexture(*texture);
        }
        m_powerUpSound.play();
        m_shield = true;
    }
}

void Hero::setJumpOn() {
    sf::Texture* texture = RM.getTexture("playerTextureUp");
    if(texture != nullptr){
        texture->setSmooth(true);
        setTexture(*texture);
    }
    m_shield = false;
}

void Hero::setStanding() {
    sf::Texture* texture = RM.getTexture("playerTexture");
    if(texture != nullptr){
        texture->setSmooth(true);
        setTexture(*texture);
    }
    m_shield = false;
}

void Hero::collisionevent() {
    if (m_shield) {
        m_shieldOnSound.play();
    } else {
        m_collisionSound.play();
    }
}










