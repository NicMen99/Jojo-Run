//
// Created by Niccolo on 25/02/2021.
//

#include "GameConfig.h"
#include "GameResourceManager.h"
#include "Platform.h"

void Platform::init(const std::string& texture_name, sf::Vector2f position, sf::Vector2f speed) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
    }

    setMPosition(position);
    setMSpeed(speed);
}

void Platform::update() {
    move();
}

void Platform::render(sf::RenderWindow& window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}

int Platform::getMSpawnPoint() const {
    return m_spawn_point;
}

void Platform::setMSpawnPoint(int mSpawnPoint) {
    m_spawn_point = mSpawnPoint;
}