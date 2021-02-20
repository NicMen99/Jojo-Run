//
// Created by Niccolo on 20/02/2021.
//

#include "GameConfig.h"
#include "GameResourceManager.h"
#include "Background.h"

void Background::init(const std::string &texture_name, bool repeated, const sf::Vector2f &scale) {
    sf::Texture * texture = RM->getTexture(texture_name);
    if(texture != nullptr) {
        texture->setRepeated(repeated);
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale.x, scale.y);
        m_sprite.setTextureRect(sf::IntRect(0, 0, (500 * GC->getWindowSize().x), GC->getWindowSize().y + static_cast<int>(GC->getGroundYpos())));
    }
}

void Background::update(sf::Vector2f offset) {
    m_sprite.move(offset.x, offset.y);
}

void Background::render(sf::RenderWindow &window) {
    window.draw(m_sprite);
}
