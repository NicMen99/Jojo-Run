//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "Background.h"

Background::Background(const std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Background, id, m_sprite)
{

}

void Background::init(const std::string & texture_name, bool repeated, const sf::Vector2f scale, const sf::Vector2f speed)
{
    std::shared_ptr<sf::Texture> texture = RM.getTexture(texture_name);
    texture->setRepeated(repeated);
    m_sprite.setTexture(*texture);
    m_sprite.setScale(scale.x, scale.y);
    m_sprite.setTextureRect(sf::IntRect(0, 0, (500 * GC.getWindowSize().x), GC.getWindowSize().y + static_cast<int>(GC.getGroundYpos())));
    m_speed = speed;
}
