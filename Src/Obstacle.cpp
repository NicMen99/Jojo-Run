//
// Created by Niccolo on 28/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Obstacle.h"

Obstacle::Obstacle(GameObjectType mtype, const std::string &name) :
    GameObject(GameObjectGroup::Map, mtype, name)
{

}

void Obstacle::init(const std::string &texture_name, sf::Vector2f scale, int damage) {
    addTexture("DEFAULT", {texture_name, false, scale, {0,0,0,0} });
    updateSprite("DEFAULT");

    m_damage = damage;
}


