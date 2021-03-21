//
// Created by Niccolo on 05/10/2020.
//

#include <iostream>
#include "GameConfig.h"

struct KeyVal{
    const char * key;
    const char * value;
};


const KeyVal resource_table [] = {
        { "blockTexture",          "Textures/blockTexture.png"},
        { "fireWallTexture",       "Textures/fireWallTexture.png"},
        { "shieldPowerUpTexture",  "Textures/shieldPowerUpTexture.png"},
        { "knifeTexture",          "Textures/knifeTexture.png"},
        { "hamonEnemyTexture",     "Textures/hamonEnemyTexture.png"},
        { "fireEnemy",             "Textures/fireEnemy.png"},
        { "emeraldEnemyTexture",   "Textures/emeraldEnemyTexture.png"},
        { "hamonBlockTexture",     "Textures/hamonBlockTexture.png"},
        { "fireBlockTexture",      "Textures/fireBlockTexture.png"},
        { "emeraldBlockTexture",   "Textures/emeraldBlockTexture.png"},
        { "playerTexture",         "Textures/playerTexture.png"},
        { "playerTextureUp",       "Textures/playerTextureUp.png"},
        { "playerShieldTexture",   "Textures/playerShieldTexture.png"},
        { "GameOverScreen",        "Textures/GameOverScreen.png"},

        { "Background1",           "Map/Background1.png"},
        { "BG",                    "Map/BG.png"},
        { "Foreground",            "Map/Foreground.png"},
        { "Middle",                "Map/Middle.png"},
        { "Platform1",             "Map/Platform.png"},

        { "soundTrack",            "Music/soundTrack.wav"},
        { "gameOverSound",         "Music/gameOverSound.wav"},
        { "collisionSound",        "Music/collisionSound.wav"},
        { "shieldSound",           "Music/shieldSound.wav"},
        { "shieldOn",              "Music/shieldOn.wav"},
        { "fireEnemyShout",        "Music/fireEnemyShout.wav"},
        { "emeraldEnemyShout",     "Music/emeraldEnemyShout.wav"},
        { "hamonEnemyShout",       "Music/hamonEnemyShout.wav"},

        { "arcadeclassic",         "Font/ARCADECLASSIC.TTF"},
        { "gameover",              "Font/GAME_OVER.TTF"}
};

void GameConfig::init() {
    for(auto i : resource_table){
        m_asset_map.insert(std::make_pair(i.key, std::string(m_asset_base_dir) + "/" + i.value));
    }
}
