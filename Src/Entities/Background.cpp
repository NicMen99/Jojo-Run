//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "ResourceManager.h"
#include "GameConfig.h"
#include "Background.h"

Background::Background(const std::string id) :
        Entity(GameObjectGroup::Map, GameObjectType::Background, id)
{

}

Background::~Background() {

}

void Background::init(GameObjectType type) {
    sf::Vector2u sz = CONFIG.getWindowSize();

    if(type == GameObjectType::Sky) {
        const std::list<Animation::FrameParams> frames = {
                {1, "BG", {0,0,0,0}, {CONFIG.getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG.getSceneSpeed().x * 0.2f), 0.f});
    }
    else if(type == GameObjectType::City) {
        const std::list<Animation::FrameParams> frames = {
                {1, "Background1", {0,0,0,0}, {CONFIG.getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG.getSceneSpeed().x * 0.1f), 0.f});
    }
    else if(type == GameObjectType::SkyScrapers) {
        const std::list<Animation::FrameParams> frames = {
                {1, "Foreground", {0,0,0,0}, {CONFIG.getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(CONFIG.getSceneSpeed().x * 0.05f), 0.f});
    }
    else if(type == GameObjectType::Bridge) {
        const std::list<Animation::FrameParams> frames = {
                {1, "Middle", {0,0,0,0}, {CONFIG.getWindowSize()}, {false, false}}
        };
        addAnimation("DEFAULT", frames);
        setSpeed({(0.f),0.f});
    }
}
