//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameObject.h"
#include "GameResourceManager.h"


GameObject::GameObject(GameObjectGroup mgroup, GameObjectType mtype, std::string mName) :
        m_group(mgroup), m_type(mtype), m_name(std::move(mName)) {

}

void GameObject::update(int32_t delta_time) {
    sf::Vector2f speed = m_speed - GC.getSceneSpeed();
    sf::Vector2f offset = {speed.x * delta_time / 1000, speed.y * delta_time / 1000};
    move(offset);
}

void GameObject::render(sf::RenderWindow & window) {
    window.draw(m_sprite);
}

void GameObject::move(const sf::Vector2f & offset) {
    m_sprite.setPosition(m_sprite.getPosition() + offset);
    if((getPosition().x + getBounds().width) < 0) {
        m_destroyed = true;
    }
}

void GameObject::applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time) {
    m_speed += {acceleration.x * delta_time / 1000, acceleration.y * delta_time / 1000};
}

void GameObject::addTexture(const std::string & texture_name, const texture_p & texture_params) {
    m_texture_map.insert(std::make_pair(texture_name, texture_params));
}

void GameObject::addSound(const std::string &sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void GameObject::updateSprite(const std::string & texture_name) {
    texture_p texture_parameters = m_texture_map[texture_name];
    if(m_active_texture != texture_parameters.name) {
        std::shared_ptr<sf::Texture> texture = RM.getTexture(texture_parameters.name);
        float scalex = texture_parameters.size.x == 0 ? 1.0f : (float)texture_parameters.size.x/texture->getSize().x;
        if(texture_parameters.hflip) scalex = -scalex;
        float scaley = texture_parameters.size.y == 0 ? 1.0f : (float)texture_parameters.size.y/texture->getSize().y;
        if(texture_parameters.vflip) scaley = -scaley;
        m_sprite.setTexture(*texture, true);
        if(scalex!=1 || scaley!=1)
            m_sprite.setScale(scalex, scaley);
        m_active_texture = texture_parameters.name;
    }
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

