//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "AnimationManager.h"

#include "Background.h"

Background::Background(const std::string id) :
        Entity(EntityGroup::Background, EntityType::SkyScrapers, id)
{

}

Background::~Background() {

}

void Background::init(EntityType type) {
    sf::Vector2u sz = CONFIG->getWindowSize();

    if(type == EntityType::Sky) {
        const std::list<FrameParams> frames = {
                {1, "BG", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG->getSceneSpeed().x * 0.2f), 0.f});
    }
    else if(type == EntityType::City) {
        const std::list<FrameParams> frames = {
                {1, "Background1", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG->getSceneSpeed().x * 0.1f), 0.f});
    }
    else if(type == EntityType::SkyScrapers) {
        const std::list<FrameParams> frames = {
                {1, "Foreground", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG->getSceneSpeed().x * 0.05f), 0.f});
    }
    else if(type == EntityType::Bridge) {
        const std::list<FrameParams> frames = {
                {1, "Middle", {0,0,0,0}, {CONFIG->getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(0.f),0.f});
    }
}
