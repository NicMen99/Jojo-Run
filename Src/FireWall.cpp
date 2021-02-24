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
    m_fireWallSpeedX = speed;
}

void FireWall::render(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

void FireWall::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

sf::Vector2f FireWall::getPosition() const {
    return m_sprite.getPosition();
}

bool FireWall::getIsMovingFW() const {
    return m_fireWallSpeedX != sf::Vector2f {0,0};
}

sf::Vector2f FireWall::getFWSpeed() const {
    return m_fireWallSpeedX;
}

int FireWall::getDamageFW() const {
    return m_damageFW;
}

void FireWall::setDamageFW(int damageFW) {
    m_damageFW = damageFW;
}

void FireWall::setFireWallSpeedX(sf::Vector2f fireWallSpeedX) {
    m_fireWallSpeedX = fireWallSpeedX;
}

sf::FloatRect FireWall::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

