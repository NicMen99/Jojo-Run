//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "Platform.h"

#include <utility>

Platform::Platform(std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Platform, std::move(id))
{

}

void Platform::init() {
//    if(m_type == GameObjectType::XPlatform)
    addTexture("DEFAULT", {"Platform1", false, {1.f, 1.f}, {0, 0, 0, 0}});
    updateSprite("DEFAULT");
}

