//
// Created by angiolo99 on 23/01/20.
//
#include "Game.h"
#include "GameResourceManager.h"
#include "Block.h"


Block::Block(std::string id) :
    Obstacle(GameObjectType::Block, id)
{

}

void Block::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed) {
    Obstacle::init(texture_name, scale, 70);
    m_speed = speed;
}

void Block::setDamageB(int damageB) {
    m_damageB = damageB;
}




