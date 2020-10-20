//
// Created by Niccolo on 05/10/2020.
//

#include <iostream>
#include "GameConfig.h"

GameConfig * GameConfig::_instance = nullptr;


GameConfig *GameConfig::instance() {
    if (_instance == nullptr) {
        _instance = new GameConfig();
    }
    return _instance;
}

void GameConfig::init(const std::string & base_dir) {
    //loadConfigFile("jojo.cfg");
    asset_base_dir = base_dir;
    asset_map = {
            std::make_pair("blockTexture",          "Textures/blockTexture.png"),
            std::make_pair("fireWallTexture",       "Textures/fireWallTexture.png"),
            std::make_pair("shieldPowerUpTexture",  "Textures/shieldPowerUpTexture.png"),
            std::make_pair("knifeTexture",          "Textures/knifeTexture.png"),
            std::make_pair("hamonEnemyTexture",     "Textures/hamonEnemyTexture.png"),
            std::make_pair("fireEnemy",             "Textures/fireEnemy.png"),
            std::make_pair("emeraldEnemyTexture",   "Textures/emeraldEnemyTexture.png"),
            std::make_pair("hamonBlockTexture",     "Textures/hamonBlockTexture.png"),
            std::make_pair("fireBlockTexture",      "Textures/fireBlockTexture.png"),
            std::make_pair("emeraldBlockTexture",   "Textures/emeraldBlockTexture.png"),
            std::make_pair("playerTexture",         "Textures/playerTexture.png"),
            std::make_pair("playerTextureUp",       "Textures/playerTextureUp.png"),
            std::make_pair("shieldPowerUpTexture",  "Textures/shieldPowerUpTexture.png"),
            std::make_pair("GameOverScreen",        "Textures/GameOverScreen.png"),

            std::make_pair("Background1",           "Map/Background1.png"),
            std::make_pair("BG",                    "Map/BG.png"),
            std::make_pair("Foreground",            "Map/Foreground.png"),
            std::make_pair("Middle",                "Map/Middle.png"),

            std::make_pair("soundTrack",            "Music/soundTrack.wav"),
            std::make_pair("gameOverSound",         "Music/gameOverSound.wav"),
            std::make_pair("collisionSound",        "Music/collisionSound.wav"),
            std::make_pair("shieldSound",           "Music/shieldSound.wav"),
            std::make_pair("shieldOn",              "Music/shieldOn.wav"),
            std::make_pair("fireEnemyShout",        "Music/fireEnemyShout.wav"),
            std::make_pair("emeraldEnemyShout",     "Music/emeraldEnemyShout.wav"),
            std::make_pair("hamonEnemyShout",       "Music/hamonEnemyShout.wav"),

            std::make_pair("arcadeclassic",         "Font/ARCADECLASSIC.TTF")
    };
}

std::string GameConfig::getAssetPath(const std::string & asset) {
    auto it = asset_map.find(asset);
    std::string path = (it == asset_map.end()) ? "" : asset_base_dir + "/" + it->second;
    if (path.empty()){
        std::cout << asset << std::endl;
    }
    return path;
}

