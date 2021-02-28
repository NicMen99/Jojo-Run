//
// Created by angiolo99 on 23/01/20.
//

#include "GameResourceManager.h"
#include "FireWall.h"

#include <utility>


FireWall::FireWall(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Wall, id, m_sprite)
{

}

void FireWall::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
}



