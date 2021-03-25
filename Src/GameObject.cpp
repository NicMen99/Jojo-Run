//
// Created by Niccolo on 25/02/2021.
//
#include <iostream>

#include "Game.h"
#include "GameConfig.h"
#include "GameObject.h"

#include <utility>
#include "GameResourceManager.h"


GameObject::GameObject(GameObjectGroup mgroup, GameObjectType mtype, std::string  mName) :
        m_group(mgroup), m_type(mtype), m_name(std::move(mName)) {
}

void GameObject::update(int32_t delta_time) {
    sf::Vector2f speed = m_speed - GC.getSceneSpeed();
    sf::Vector2f offset = {speed.x * delta_time / 1000, speed.y * delta_time / 1000};
    move(offset);
    m_animator.update(delta_time);
}

void GameObject::render(sf::RenderWindow & window) {
    auto frame = m_animator.getCurrentFrame();
    frame->setPosition(getPosition());
    /*
    if(getName() == "Fire")
        std::cout << getName() << " " << frame->getPosition().x << "," << frame->getPosition().y << std::endl;
    */
    window.draw(*frame);
}

void GameObject::move(const sf::Vector2f & offset) {
    setPosition(getPosition() + offset);
//    m_animator.getCurrentFrame()->setPosition(getPosition());
    if((getPosition().x + getBounds().width) < 0) {
        m_destroyed = true;
    }
}

void GameObject::applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time) {
    m_speed += {acceleration.x * delta_time / 1000, acceleration.y * delta_time / 1000};
}

sf::FloatRect GameObject::getBounds() const {
    sf::FloatRect bounds = m_animator.getCurrentFrame()->getGlobalBounds();
    bounds.left = m_position.x;
    bounds.top = m_position.y;
    return bounds;
}



void GameObject::addSound(const std::string &sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void GameObject::playSound(const std::string & sound_name, float volume) {
    std::string sound_resource = m_sound_map[sound_name];
    if(m_active_sound != sound_resource) {
        std::shared_ptr<sf::SoundBuffer> resource = RM.getSound(sound_resource);
        m_sound.setBuffer(*resource);
        m_active_sound = sound_resource;
    }
    m_sound.setVolume(volume);
    m_sound.play();
}

