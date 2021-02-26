//
// Created by Niccolo on 20/02/2021.
//

#include "GameConfig.h"
#include "GameResourceManager.h"
#include "Background.h"

void Background::init(const std::string &texture_name, sf::Vector2f speed, bool repeated, const sf::Vector2f &scale) {
    sf::Texture * texture = RM->getTexture(texture_name);
    if(texture != nullptr) {
        texture->setRepeated(repeated);
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale.x, scale.y);
        m_sprite.setTextureRect(sf::IntRect(0, 0, (500 * GC->getWindowSize().x), GC->getWindowSize().y + static_cast<int>(GC->getGroundYpos())));
        setMSpeed(speed);
    }
}

void Background::update(int32_t delta_time) {
    sf::Vector2f offset = {getMSpeed().x * delta_time, getMSpeed().y * delta_time};
    move(offset);
}

void Background::render(sf::RenderWindow &window) {
    m_sprite.setPosition(getMPosition());
    window.draw(m_sprite);
}
