//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "FireWall.h"

FireWall::FireWall(std::string id) :
    Obstacle(GameObjectType::Wall, id)
{

}

void FireWall::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed) {
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
}



