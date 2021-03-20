//
// Created by angiolo99 on 10/02/20.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "PowerUp.h"

PowerUp::PowerUp(GameObjectType mtype, const std::string &mName) :
    GameObject(GameObjectGroup::Powerup, mtype, mName)
{

}

void PowerUp::init(const std::string &texture_name, sf::Vector2f scale, sf::Vector2f speed)
{
    addTexture("DEFAULT", {texture_name, false, scale, {0,0,0,0} });
    updateSprite("DEFAULT");

    m_speed = speed;
}

