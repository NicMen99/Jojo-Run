//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "Background.h"

Background::Background(const std::string id) :
    GameObject(GameObjectGroup::Map, GameObjectType::Background, id)
{

}

void Background::init(GameObjectType type) {
    sf::Vector2u sz = GC.getWindowSize();

    if(type == GameObjectType::Sky) {
        addTexture("DEFAULT", {"BG", GC.getWindowSize(), false, false});
        setSpeed({(GC.getSceneSpeed().x*0.2f),0.f});
        updateSprite("DEFAULT");
    }
    else if(type == GameObjectType::City) {
        addTexture("DEFAULT", {"Background1", GC.getWindowSize(), false, false});
        setSpeed({(GC.getSceneSpeed().x*0.1f),0.f});
        updateSprite("DEFAULT");
    }
    else if(type == GameObjectType::SkyScrapers) {
        addTexture("DEFAULT", {"Foreground", GC.getWindowSize(), false, false});
        setSpeed({(GC.getSceneSpeed().x*0.05f),0.f});
        updateSprite("DEFAULT");
    }
    else if(type == GameObjectType::Bridge) {
        addTexture("DEFAULT", {"Middle", GC.getWindowSize(), false, false});
        setSpeed({(0.f),0.f});
        updateSprite("DEFAULT");
    }
}
