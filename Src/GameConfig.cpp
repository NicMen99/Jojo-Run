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
        /* Textures */
        {"PLATFORM",               "Map/Platform.png"},

        {"PLAYER_RUN",             "Textures/PlayerRun.png"},
        {"PLAYER_RUN_SHIELD",      "Textures/PlayerRunShield.png"},
        {"PLAYER_JUMP",            "Textures/PlayerJump.png"},
        {"PLAYER_ATTACK",          "Textures/PlayerAttack.png"},
        {"PLAYER_DEATH",           "Textures/PlayerDeath.png"},

        {"EMERALD_ENEMY_IDLE",     "Textures/EmeraldEnemyIdle.png"},     //@TODO rigirare, rinominare
        {"EMERALD_ENEMY_DEATH",    "Textures/EmeraldEnemyDeath.png"},

        {"HAMON_ENEMY_IDLE",       "Textures/HamonEnemyIdle.png"},     //@TODO rigirare, rinominare
        {"HAMON_ENEMY_ATTACK",     "Textures/HamonEnemyAttack.png"},
        {"HAMON_ENEMY_DEATH",      "Textures/HamonEnemyDeath.png"},

        {"FIRE_ENEMY_IDLE",        "Textures/FireEnemyIdle.png"},
        {"FIRE_ENEMY_ATTACK",      "Textures/FireEnemyAttack.png"},
        {"FIRE_ENEMY_DEATH",       "Textures/FireEnemyDeath.png"},

        { "SPLASH_SCREEN",         "Textures/GameOverScreen.png"},
        { "GAME_OVER_SCREEN",      "Textures/GameOverScreen.png"},

        /* Fonts */
        { "GAME_OVER_FONT",        "Font/GAME_OVER.TTF"},

        /* Sounds */

        /**/
        { "blockTexture",          "Textures/blockTexture.png"},
        { "fireWallTexture",       "Textures/fireWallTexture.png"},
        { "shieldPowerUpTexture",  "Textures/shieldPowerUpTexture.png"},
        { "knifeTexture",          "Textures/knifeTexture.png"},
        { "fireEnemyTexture",      "Textures/fireEnemyTexture.png"},
        { "hamonBlockTexture",     "Textures/hamonBlockTexture.png"},
        { "fireBlockTexture",      "Textures/fireBlockTexture.png"},
        { "emeraldBlockTexture",   "Textures/emeraldBlockTexture.png"},
        { "playerTexture",         "Textures/playerTexture.png"},
        { "playerShieldTexture",   "Textures/playerShieldTexture.png"},
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
};

void GameConfig::init() {
    for(auto i : resource_table){
        m_asset_map.insert(std::make_pair(i.key, std::string(m_asset_base_dir) + "/" + i.value));
    }
}
