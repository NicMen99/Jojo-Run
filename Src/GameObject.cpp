//
// Created by Niccolo on 25/02/2021.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameObject.h"
#include "GameResourceManager.h"


GameObject::GameObject(GameObjectGroup mgroup, GameObjectType mtype, std::string mName, sf::Sprite &mSprite) :
        m_group(mgroup), m_type(mtype), m_name(std::move(mName)), m_active_sprite(mSprite) {

}

void GameObject::update(int32_t delta_time) {
    sf::Vector2f speed = m_speed - GC.getSceneSpeed();
    sf::Vector2f offset = {speed.x * delta_time / 1000, speed.y * delta_time / 1000};
    move(offset);
}

void GameObject::render(sf::RenderWindow & window) {
    window.draw(m_active_sprite);
}

void GameObject::move(const sf::Vector2f & offset) {
    m_active_sprite.setPosition(m_active_sprite.getPosition() + offset);
    if((getPosition().x + getBounds().width) < 0) {
        m_destroyed = true;
    }
}

void GameObject::applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time) {
    m_speed += {acceleration.x * delta_time / 1000, acceleration.y * delta_time / 1000};
}

void GameObject::addSound(const std::string &sound_name, const std::string &sound_resource, float volume) {
    std::shared_ptr<sf::SoundBuffer> resource = RM.getSound(sound_resource);
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();
    sound->setBuffer(*resource);
    sound->setVolume(volume);
    m_sound_map.insert(std::make_pair(sound_name, sound));
}

void GameObject::playSound(const std::string &sound_name) {
    if(m_sound_map.count(sound_name) > 0)
        m_sound_map[sound_name]->play();
}