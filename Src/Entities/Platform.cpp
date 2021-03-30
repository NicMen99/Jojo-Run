//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "ResourceManager.h"
#include "Platform.h"

#include <utility>

Platform::Platform(std::string id) :
        Entity(GameObjectGroup::Map, GameObjectType::Platform, std::move(id))
{

}

Platform::~Platform() {

}

void Platform::init() {
    const std::list<Animation::FrameParams> frames = {
            {1, "Platform1", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
}
