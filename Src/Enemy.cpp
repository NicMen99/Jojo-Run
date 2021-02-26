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
    setMSpeed(speed);
}

void Enemy::update(int32_t delta_time) {
    sf::Vector2f offset = {getMSpeed().x * delta_time, getMSpeed().y * delta_time};
    move(offset);
}

void Enemy::render(sf::RenderWindow & window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}

int Enemy::getDamage() const {
    return m_damage;
}

void Enemy::setDamage(int damage) {
    m_damage = damage;
}

void Enemy::setEnemyPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}








