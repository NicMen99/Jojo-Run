//
// Created by Niccolo on 30/03/2021.
//

#include <memory>
#include <iostream>

#include "Game.h"
#include "SoundManager.h"

SoundManager::SoundManager(){

}

SoundManager::~SoundManager(){

}

void SoundManager::addSound(const std::string & sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void SoundManager::playSound(const std::string &sound_name, float volume) {
    std::string sound_resource = m_sound_map[sound_name];
    if(m_active_sound != sound_resource) {
        std::shared_ptr<sf::SoundBuffer> sound = RESOURCE->getSound(sound_resource);
        m_sound.setBuffer(*sound);
        m_active_sound = sound_resource;
    }
    m_sound.setVolume(volume);
    m_sound.play();
}
