//
// Created by angiolo99 on 10/02/20.
//

#include <string>
#include "GameResourceManager.h"
#include "PowerUp.h"

void PowerUp::init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale, bool isShield, bool isKnife, bool isThrown) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    setMSpeed(speed);
    m_isShield = isShield;
    m_isKnife = isKnife;
    if (m_isKnife){
        m_sprite.setRotation(45.f);
    }
    m_isThrowable = isThrown;
}

void PowerUp::update(int32_t delta_time) {
    sf::Vector2f offset = {getMSpeed().x * delta_time, getMSpeed().y * delta_time};
    move(offset);
}

void PowerUp::render(sf::RenderWindow &window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}

void PowerUp::setIsShield(bool isShield) {
    m_isShield = isShield;
}

void PowerUp::setIsKnife(bool isKnife) {
    m_isKnife = isKnife;
}

void PowerUp::setIsThrowable(bool isThrowable) {
    m_isThrowable = isThrowable;
}

bool PowerUp::getisShield() const {
    return m_isShield;
}

bool PowerUp::getisKnife() const {
    return m_isKnife;
}

bool PowerUp::getisThrowable() const {
    return m_isThrowable;
}

void PowerUp::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

