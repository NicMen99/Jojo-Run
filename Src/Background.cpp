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

void Background::init(const std::string & texture_name, bool repeated, const sf::Vector2f scale, const sf::Vector2f speed) {

    addTexture("DEFAULT", {texture_name, repeated, scale, sf::IntRect{0,0, (int)GC.getWindowSize().x, (int)GC.getWindowSize().y}});
    updateSprite("DEFAULT");

    m_speed = speed;
}
