//
// Created by angiolo99 on 23/01/20.
//
#include "Block.h"
#include "GameResourceManager.h"


void Block::init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    setMSpeed(speed);
}

void Block::update(int32_t delta_time) {
    sf::Vector2f offset = {getMSpeed().x * delta_time, getMSpeed().y * delta_time};
    move(offset);
}

void Block::render(sf::RenderWindow & window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}


int Block::getDamageB() const {
    return m_damageB;
}

void Block::setDamageB(int damageB) {
    m_damageB = damageB;
}

void Block::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

sf::Vector2f Block::getPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect Block::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}



