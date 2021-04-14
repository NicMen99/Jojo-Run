#include "MockGameConfig.h"

void MockGameConfig::setGravity(sf::Vector2f gravity) {
    m_gravity = gravity;
}

void MockGameConfig::setSceneSpeed(sf::Vector2f speed) {
    m_scene_speed = speed;
}

void MockGameConfig::init() {
    m_asset_base_dir = "TestAssets";
    GameConfig::init();
}

void MockGameConfig::clear() {
    m_asset_map.clear();
}

void MockGameConfig::setMapResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Map/" + asset_path));
}

void MockGameConfig::setTextureResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Textures/" + asset_path));
}

void MockGameConfig::setFontResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Font/" + asset_path));
}

void MockGameConfig::setSoundResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Music/" + asset_path));
}
