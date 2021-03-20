//
// Created by Niccolo on 28/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Obstacle.h"

Obstacle::Obstacle(GameObjectType mtype, const std::string &name) :
    GameObject(GameObjectGroup::Map, mtype, name, m_sprite)
{

}

void Obstacle::init(const std::string &texture_name, sf::Vector2f scale, int damage) {
    std::shared_ptr<sf::Texture> texture = RM.getTexture(texture_name);
    m_sprite.setTexture(*texture);
    m_sprite.setScale(scale);
    m_damage = damage;
}


