//
// Created by angiolo99 on 29/01/20.
//

#include "GameResourceManager.h"
#include "Enemy.h"

void Enemy::init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
}

void Enemy::render(sf::RenderWindow & window) {
    window.draw(m_sprite);
}

sf::Vector2f Enemy::getSpeed() const {
    return m_speed;
}

void Enemy::setSpeed(sf::Vector2f speed) {
    m_speed = speed;
}

int Enemy::getDamage() const {
    return m_damage;
}

void Enemy::setDamage(int damage) {
    m_damage = damage;
}

void Enemy::setIsMovingEnemy(bool ismovingEnemy) {
     m_isMovingEnemy = ismovingEnemy;
}

bool Enemy::getIsMovingEnemy() const {
    return m_isMovingEnemy;
}

void Enemy::setEnemyPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}








