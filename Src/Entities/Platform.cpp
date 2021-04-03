//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "AnimationManager.h"
#include "Platform.h"

Platform::Platform(std::string id) :
        Entity(EntityGroup::Platform, EntityType::StonePlatform, std::move(id))
{

}

Platform::~Platform() {

}

void Platform::init() {
    setSpeed(0, 0);
}