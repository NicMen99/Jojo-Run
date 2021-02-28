//
// Created by angiolo99 on 10/02/20.
//

#include <string>
#include "Game.h"
#include "PowerUp.h"

PowerUp::PowerUp(GameObjectType mtype, const std::string &mName) :
    GameObject(GameObjectGroup::Powerup, mtype, mName, m_sprite)
{

}

void PowerUp::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed)
{
    sf::Texture* texture = RM.getTexture(texture_name);
    if(texture != nullptr){
        m_sprite.setTexture(*texture);
        m_sprite.setScale(scale);
    }
    m_speed = speed;
}

