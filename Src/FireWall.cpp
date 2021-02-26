//
// Created by angiolo99 on 23/01/20.
//

#include "GameResourceManager.h"
#include "FireWall.h"


void FireWall::init(const std::string &texture_name, sf::Vector2f speed, sf::Vector2f scale) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    setMSpeed(speed);
}

void FireWall::update(int32_t delta_time) {
    sf::Vector2f offset = {getMSpeed().x * delta_time, getMSpeed().y * delta_time};
    move(offset);
}

void FireWall::render(sf::RenderWindow &window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}

void FireWall::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

sf::Vector2f FireWall::getPosition() const {
    return m_sprite.getPosition();
}

int FireWall::getDamageFW() const {
    return m_damageFW;
}

void FireWall::setDamageFW(int damageFW) {
    m_damageFW = damageFW;
}

sf::FloatRect FireWall::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

