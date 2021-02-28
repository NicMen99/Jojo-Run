//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameResourceManager.h"

sf::Texture* GameResourceManager::getTexture(const std::string & texture) {
    auto it = m_texture_map.find(texture);
    if(it != m_texture_map.end()) {
        return &it->second;
    }

    std::string path = GC.getAssetPath(texture);
    if(path.empty()) {
        return nullptr;
    }

    sf::Texture& resource = m_texture_map[texture];
    bool result = resource.loadFromFile(path);
    return & resource;
}

sf::SoundBuffer* GameResourceManager::getSound(const std::string &sound) {
    auto it = m_sound_map.find(sound);
    if(it != m_sound_map.end()) {
        return &it->second;
    }

    std::string path = GC.getAssetPath(sound);
    if(path.empty()) {
        return nullptr;
    }

    sf::SoundBuffer& resource = m_sound_map[sound];
    resource.loadFromFile(path);
    return & resource;
}

sf::Font *GameResourceManager::getFont(const std::string &font) {
    auto it = m_font_map.find(font);
    if(it != m_font_map.end()) {
        return &it->second;
    }

    std::string path = GC.getAssetPath(font);
    if(path.empty()) {
        return nullptr;
    }

    sf::Font& resource = m_font_map[font];
    resource.loadFromFile(path);
    return & resource;}



