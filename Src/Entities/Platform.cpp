//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "AnimationManager.h"
#include "Platform.h"

Platform::Platform(std::string id) :
        Entity(EntityGroup::Map, EntityType::Platform, std::move(id))
{

}

Platform::~Platform() {

}

void Platform::init() {
    const std::list<FrameParams> frames = {
            {1, "Platform1", {0,0,0,0}, {0,0}, {false, false}}
    };
    addAnimation("DEFAULT", frames);
}
