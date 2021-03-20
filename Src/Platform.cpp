//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Platform.h"

Platform::Platform(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Platform, id)
{

}

void Platform::init(const std::string& texture_name, sf::Vector2f speed) {
    addTexture("DEFAULT", {texture_name, false, {1.f, 1.f}, {0,0,0,0} });
    updateSprite("DEFAULT");

    m_speed = speed;
}

