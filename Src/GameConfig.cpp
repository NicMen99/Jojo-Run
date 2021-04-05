//
// Created by Niccolo on 05/10/2020.
//

#include <iostream>
#include "GameConfig.h"

struct KeyVal{
    const char * key;
    const char * value;
};


GameConfig::GameConfig() {

}

GameConfig::~GameConfig() {

}

const KeyVal resource_table [] = {
        {"PLATFORM",               "Map/Platform.png"},
        {"PLAYER_RUN",             "Textures/PlayerRun.png"},
        {"PLAYER_RUN_SHIELD",      "Textures/PlayerRunShield.png"},
        {"PLAYER_JUMP",            "Textures/PlayerJump.png"}, //@todo: REINOMINARE

        { "blockTexture",          "Textures/blockTexture.png"},
        { "fireWallTexture",       "Textures/fireWallTexture.png"},
        { "shieldPowerUpTexture",  "Textures/shieldPowerUpTexture.png"},
        { "knifeTexture",          "Textures/knifeTexture.png"},
        { "hamonEnemyTexture",     "Textures/hamonEnemyTexture.png"},
        { "fireEnemyTexture",      "Textures/fireEnemyTexture.png"},
        { "emeraldEnemyTexture",   "Textures/emeraldEnemyTexture.png"},
        { "hamonBlockTexture",     "Textures/hamonBlockTexture.png"},
        { "fireBlockTexture",      "Textures/fireBlockTexture.png"},
        { "emeraldBlockTexture",   "Textures/emeraldBlockTexture.png"},
        { "playerTexture",         "Textures/playerTexture.png"},
        { "playerShieldTexture",   "Textures/playerShieldTexture.png"},
        { "GameOverScreen",        "Textures/GameOverScreen.png"},
        { "Fire",                  "Textures/FirewallAnimation.png"},

        { "Background1",           "Map/Background1.png"},
        { "BG",                    "Map/BG.png"},
        { "Foreground",            "Map/Foreground.png"},
        { "Middle",                "Map/Middle.png"},

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
