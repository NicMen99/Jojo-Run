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
    Obstacle::init(texture_name, scale, 1);
    m_speed = speed;
}
