//
// Created by angiolo99 on 23/01/20.
//
#include "Block.h"
#include "GameResourceManager.h"


Block::Block(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Block, id, m_sprite)
{

}

void Block::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed) {
    sf::Texture* texture = RM->getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
}

void Block::setDamageB(int damageB) {
    m_damageB = damageB;
}




