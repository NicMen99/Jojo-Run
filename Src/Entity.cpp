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
    m_prev_frame = m_frame;
    m_frame = m_animator.getCurrentFrame()->getGlobalBounds();
    setPosition(getPrevPosition());
    move(delta_time);
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
    m_frame = getBounds();
    sf::RectangleShape hitbox;
    hitbox.setPosition(m_frame.left, m_frame.top);
    hitbox.setSize({m_frame.width, m_frame.height});
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);
    window.draw(hitbox);
#endif
    /**/
}

void Entity::move(int32_t delta_time) {
    sf::Vector2f speed = m_speed - CONFIG.getSceneSpeed();
    sf::Vector2f offset = {speed.x * delta_time / 1000, speed.y * delta_time / 1000};
    setPosition(getPosition() + offset);
    if((getPosition().x + getBounds().width) < 0) {
        m_destroyed = true;
    }
}

void Entity::applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time) {
    m_speed += {acceleration.x * delta_time / 1000, acceleration.y * delta_time / 1000};
}

void Entity::addAnimation(const std::string & animation_name, const std::list<Animation::FrameParams>& frames) {
    m_animator.addAnimation(animation_name, frames);
    sf::FloatRect frame = m_animator.getCurrentFrame()->getGlobalBounds();
    setPosition(getPosition());
    m_frame = frame;
}

void Entity::playAnimation(const std::string & animation_name, int repetitions) {
    m_animator.play(animation_name, repetitions);
}


void Entity::addSound(const std::string &sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void Entity::playSound(const std::string & sound_name, float volume) {
    std::string sound_resource = m_sound_map[sound_name];
    if(m_active_sound != sound_resource) {
        std::shared_ptr<sf::SoundBuffer> resource = RESOURCE.getSound(sound_resource);
        m_sound.setBuffer(*resource);
        m_active_sound = sound_resource;
    }
    m_sound.setVolume(volume);
    m_sound.play();
}

