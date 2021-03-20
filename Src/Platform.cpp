//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Platform.h"

Platform::Platform(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Platform, id, m_sprite)
{

}

void Platform::init(const std::string& texture_name, sf::Vector2f speed) {
    std::shared_ptr<sf::Texture> texture = RM.getTexture(texture_name);
    m_sprite.setTexture(*texture);
    m_speed = speed;
}

