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
    auto animation = m_animator.createAnimation();
    animation->addFrame("Platform1");
    m_animator.play();
}

