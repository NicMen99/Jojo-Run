//
// Created by Niccolo on 30/03/2021.
//

#include <memory>
#include <iostream>

#include "Game.h"
#include "SoundManager.h"

SoundManager::SoundManager() {
}

SoundManager::~SoundManager() {
}

void SoundManager::clear() {
    m_active_sound = "";
    m_sound_map.clear();
}

void SoundManager::addSound(const std::string & sound_name, const std::string & sound_resource) {
    m_sound_map.insert(std::make_pair(sound_name, sound_resource));
}

void SoundManager::playSound(const std::string &sound_name, float volume) {
    std::string sound_resource = m_sound_map[sound_name];
    /*
    if(sound_resource == m_active_sound && m_sound.getStatus() == sf::Sound::Playing)
        return;
    */
    if(m_active_sound != sound_resource) {
        std::shared_ptr<sf::SoundBuffer> sound = RESOURCE->getSound(sound_resource);
        m_sound.setBuffer(*sound);
        m_active_sound = sound_resource;
    }
    m_sound.setVolume(volume);
    m_sound.play();
}

void SoundManager::playMusic(const std::string &sound_name, float volume, float pitch) {
    if(!sound_name.empty())
        m_music.openFromFile(CONFIG->getAssetPath(sound_name));
    m_music.setVolume(volume);
    m_music.setPitch(pitch);
    m_music.play();
}

void SoundManager::setVolume(float volume) {
    m_music.setVolume(volume);
}

void SoundManager::setPitch(float pitch) {
    m_music.setPitch(pitch);
}

void SoundManager::stopMusic() {
    m_music.stop();
}
