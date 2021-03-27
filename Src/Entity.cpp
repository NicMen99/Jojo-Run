//
// Created by Niccolo on 25/02/2021.
//
#include <cassert>
#include <iostream>

#include "Game.h"
#include "GameConfig.h"
#include "Entity.h"

#include "ResourceManager.h"


Entity::Entity(GameObjectGroup mgroup, GameObjectType mtype, std::string  mName) :
        m_group(mgroup),
        m_type(mtype),
        m_name(std::move(mName)) {
}

void Entity::update(int32_t delta_time) {
    sf::Vector2f speed = m_speed - GC.getSceneSpeed();
    sf::Vector2f offset = {speed.x * delta_time / 1000, speed.y * delta_time / 1000};
    move(offset);
    m_animator.update(delta_time);
}

void Entity::render(sf::RenderWindow & window) {
    auto frame = m_animator.getCurrentFrame();
    assert(frame!=nullptr);
    frame->setPosition(getPosition());
    //std::cout << getName() << " " << frame->getPosition().x << "," << frame->getPosition().y << std::endl;
    window.draw(*frame);

    /**/
#ifdef HIT_BOX_DEBUG
    m_bounds = getBounds();
    sf::RectangleShape hitbox;
    hitbox.setPosition(m_bounds.left, m_bounds.top);
    hitbox.setSize({m_bounds.width, m_bounds.height});
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);
    window.draw(hitbox);
#endif
    /**/
}

void Entity::move(const sf::Vector2f & offset) {
    setPosition(getPosition() + offset);
    if((getPosition().x + getBounds().width) < 0) {
        m_destroyed = true;
    }
}

void Entity::applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time) {
    m_speed += {acceleration.x * delta_time / 1000, acceleration.y * delta_time / 1000};
}

sf::FloatRect Entity::getBounds() const {
    auto frame = m_animator.getCurrentFrame();
    assert(frame!=nullptr);
    sf::FloatRect bounds = frame->getGlobalBounds();
    bounds.left = m_position.x;
    bounds.top = m_position.y;
    //std::cout << getName() << " " << bounds.left << "," << bounds.top << "," << bounds.width << "," << bounds.height << std::endl;
    return bounds;
}



void Entity::addSound(const std::string &sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void Entity::playSound(const std::string & sound_name, float volume) {
    std::string sound_resource = m_sound_map[sound_name];
    if(m_active_sound != sound_resource) {
        std::shared_ptr<sf::SoundBuffer> resource = RM.getSound(sound_resource);
        m_sound.setBuffer(*resource);
        m_active_sound = sound_resource;
    }
    m_sound.setVolume(volume);
    m_sound.play();
}

