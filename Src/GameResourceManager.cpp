//
// Created by Niccolo on 20/02/2021.
//

#include "GameConfig.h"
#include "GameResourceManager.h"

GameResourceManager * GameResourceManager::_instance = nullptr;

GameResourceManager *GameResourceManager::instance() {
    if (_instance == nullptr) {
        _instance = new GameResourceManager();
    }
    return _instance;
}

sf::Texture* GameResourceManager::getTexture(const std::string & texture) {

    auto it = m_texture_map.find(texture);
    if(it != m_texture_map.end()) {
        return &it->second;
    }

    std::string path = GameConfig::instance()->getAssetPath(texture);
    if(path.empty()) {
        return nullptr;
    }

    sf::Texture& resource = m_texture_map[texture];
    resource.loadFromFile(path);
    return & resource;
}

