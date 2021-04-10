#include "TestGameConfig.h"

void TestGameConfig::setSceneSpeed(sf::Vector2f speed) {
    m_scene_speed = speed;
}

void TestGameConfig::init() {
    m_asset_base_dir = "TestAssets";
    GameConfig::init();
}

void TestGameConfig::clear() {
    m_asset_map.clear();
}

void TestGameConfig::setMapResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Map/" + asset_path));
}

void TestGameConfig::setTextureResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Textures/" + asset_path));
}

void TestGameConfig::setFontResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Font/" + asset_path));
}

void TestGameConfig::setSoundResource(const std::string & name, const std::string & asset_path){
    m_asset_map.insert(std::make_pair(name, "TestAssets/Music/" + asset_path));
}
