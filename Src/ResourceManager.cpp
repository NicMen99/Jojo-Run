//
// Created by Niccolo on 20/02/2021.
//

#include "Game.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {

}

void ResourceManager::clearTextureCache() {
    m_texture_map.clear();
}

void ResourceManager::clearFontCache() {
    m_font_map.clear();
}

void ResourceManager::clearSoundCache() {
    m_sound_map.clear();
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string & texture) {
    auto it = m_texture_map.find(texture);
    if(it != m_texture_map.end()) {
        return it->second;
    }
    std::shared_ptr<sf::Texture> resource = std::make_shared<sf::Texture>();
    bool result = resource->loadFromFile(CONFIG->getAssetPath(texture));
#ifdef GAMEDEBUG
    assert(result);
#endif
    if(!result)
        return nullptr;
    /* mette nella cache */
    m_texture_map[texture] = resource;
    return m_texture_map[texture];
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::getSound(const std::string & sound) {
    auto it = m_sound_map.find(sound);
    if(it != m_sound_map.end()) {
        return it->second;
    }
    std::shared_ptr<sf::SoundBuffer> resource = std::make_shared<sf::SoundBuffer>();
    bool result = resource->loadFromFile(CONFIG->getAssetPath(sound));
#ifdef GAMEDEBUG
    assert(result);
#endif
    if(!result)
        return nullptr;
    /* mette nella cache */
    m_sound_map[sound] = resource;
    return m_sound_map[sound];
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string & font) {
    auto it = m_font_map.find(font);
    if(it != m_font_map.end()) {
        return it->second;
    }
    std::shared_ptr<sf::Font> resource = std::make_shared<sf::Font>();
    bool result = resource->loadFromFile(CONFIG->getAssetPath(font));
#ifdef GAMEDEBUG
    assert(result);
#endif
    if(!result)
        return nullptr;
    /* mette nella cache */
    m_font_map[font] = resource;
    return m_font_map[font];
}
