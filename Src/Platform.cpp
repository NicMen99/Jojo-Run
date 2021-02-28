//
// Created by Niccolo on 25/02/2021.
//

#include "GameConfig.h"
#include "GameResourceManager.h"
#include "Platform.h"

Platform::Platform(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Platform, id, m_sprite)
{

}

void Platform::init(const std::string& texture_name, sf::Vector2f speed) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_speed = speed;
    }
}

