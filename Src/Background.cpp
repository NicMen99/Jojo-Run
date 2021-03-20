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

    addTexture("DEFAULT", {texture_name, repeated, scale, sf::IntRect{0,0,static_cast<int>(500 * GC.getWindowSize().x),                                        static_cast<int>((GC.getWindowSize().y + GC.getGroundYpos()))}});
    updateSprite("DEFAULT");

    m_speed = speed;
}
