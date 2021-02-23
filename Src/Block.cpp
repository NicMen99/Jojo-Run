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
    m_speed = speed;
}


void Block::render(sf::RenderWindow & window) {
    window.draw(m_sprite);
}

bool Block::getIsMovingBlock() const {
    return m_speed != sf::Vector2f {0, 0};
}

float Block::getBlockSpeedX() const {
    return m_speed.x;
}

int Block::getDamageB() const {
    return damageB;
}

void Block::setDamageB(int damageB) {
    Block::damageB = damageB;
}

void Block::setBlockSpeedX(float blockSpeedX) {
    m_speed = sf::Vector2f (blockSpeedX, 0);
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

