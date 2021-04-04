//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "Background.h"

Background::Background(const std::string id) :
        Entity(EntityGroup::Background, EntityType::SkyScrapers, id)
{

}

Background::~Background() {

}

void Background::init(EntityType type) {
    if(type == EntityType::Sky) {
        setSpeed({(CONFIG->getSceneSpeed().x * 0.2f), 0.f});
    }
    else if(type == EntityType::City) {
        setSpeed({(CONFIG->getSceneSpeed().x * 0.1f), 0.f});
    }
    else if(type == EntityType::SkyScrapers) {
        setSpeed({(CONFIG->getSceneSpeed().x * 0.05f), 0.f});
    }
    else if(type == EntityType::Bridge) {
        setSpeed({(0.f),0.f});
    }
}
