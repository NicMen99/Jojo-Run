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
        auto animation = m_animator.createAnimation();
        animation->addFrame("BG", {0,0,0,0}, 1, {GC.getWindowSize().x, GC.getWindowSize().y});
        m_animator.play();
        setSpeed({(GC.getSceneSpeed().x*0.2f),0.f});
    }
    else if(type == GameObjectType::City) {
        auto animation = m_animator.createAnimation();
        animation->addFrame("Background1", {0,0,0,0}, 1, {GC.getWindowSize().x, GC.getWindowSize().y});
        m_animator.play();
        setSpeed({(GC.getSceneSpeed().x*0.1f),0.f});
    }
    else if(type == GameObjectType::SkyScrapers) {
        auto animation = m_animator.createAnimation();
        animation->addFrame("Foreground", {0,0,0,0}, 1, {GC.getWindowSize().x, GC.getWindowSize().y});
        m_animator.play();
        setSpeed({(GC.getSceneSpeed().x*0.05f),0.f});
    }
    else if(type == GameObjectType::Bridge) {
        auto animation = m_animator.createAnimation();
        animation->addFrame("Middle", {0,0,0,0}, 1, {GC.getWindowSize().x, GC.getWindowSize().y});
        m_animator.play();
        setSpeed({(0.f),0.f});
    }
}
