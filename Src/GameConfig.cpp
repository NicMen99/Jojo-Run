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
        {"PLATFORM",                    "Map/StonePlatform.png"},

        {"PLAYER_RUN",                  "Textures/PlayerRun.png"},
        {"PLAYER_RUN_SHIELD",           "Textures/PlayerRunShield.png"},
        {"PLAYER_JUMP",                 "Textures/PlayerJump.png"},
        {"PLAYER_ATTACK",               "Textures/PlayerAttack.png"},
        {"PLAYER_DEATH",                "Textures/PlayerDeath.png"},

        {"EMERALD_ENEMY_IDLE",          "Textures/EmeraldEnemyIdle.png"},
        {"EMERALD_ENEMY_ATTACK",        "Textures/EmeraldEnemyAttack.png"},
        {"EMERALD_ENEMY_DEATH",         "Textures/EmeraldEnemyDeath.png"},

        {"HAMON_ENEMY_IDLE",            "Textures/HamonEnemyIdle.png"},
        {"HAMON_ENEMY_ATTACK",          "Textures/HamonEnemyAttack.png"},
        {"HAMON_ENEMY_DEATH",           "Textures/HamonEnemyDeath.png"},

        {"FIRE_ENEMY_IDLE",             "Textures/FireEnemyIdle.png"},
        {"FIRE_ENEMY_ATTACK",           "Textures/FireEnemyAttack.png"},
        {"FIRE_ENEMY_DEATH",            "Textures/FireEnemyDeath.png"},

        {"LIGHTING",                    "Textures/LightingBlock.png"},
        {"FIRE",                        "Textures/FirewallBlock.png"},

        {"EMERALD_BULLET",              "Textures/EmeraldBullet.png"},
        {"FIRE_BULLET",                 "Textures/FireBullet.png"},
        {"KNIFE_BULLET",                "Textures/KnifeBullet.png"},

        {"SHIELD_PWUP",                 "Textures/ShieldPowerup.png"},
        {"WEAPON_PWUP",                 "Textures/WeaponPowerup.png"},

        { "PLAYER_ICON",                "Textures/PlayerIcon.png"},
        { "SPLASH_SCREEN",              "Textures/SplashScreen.png"},
        { "GAME_OVER_SCREEN",           "Textures/GameOverScreen.png"},

        /* Fonts */
        { "GAME_OVER_FONT",             "Font/GAME_OVER.TTF"},
        { "RETRO_GAMING_FONT",          "Font/RetroGaming.ttf"},

        /* Sounds */
        { "SOUND_TRACK",                "Music/SoundTrack.wav"},
        { "PLAYER_ATTACK_SOUND",        "Music/PlayerAttackSound.wav"},
        { "PLAYER_DEATH_SOUND",         "Music/PlayerDeathSound.wav"},
        { "PLAYER_HIT_SOUND",           "Music/PlayerHitSound.wav"},
        { "PLAYER_SHIELD_HIT_SOUND",    "Music/PlayerShieldHitSound.wav"},
        { "PLAYER_SHIELD_PICK_SOUND",   "Music/PlayerShieldPickSound.wav"},
        { "EMERALD_ATTACK_SOUND",       "Music/EmeraldAttackSound.wav"},
        { "EMERALD_DEATH_SOUND",        "Music/EmeraldDeathSound.wav"},
        { "HAMON_ATTACK_SOUND",         "Music/HamonAttackSound.wav"},
        { "HAMON_DEATH_SOUND",          "Music/HamonDeathSound.wav"},
        { "FIRE_ATTACK_SOUND",          "Music/FireAttackSound.wav"},
        { "FIRE_DEATH_SOUND",           "Music/FireDeathSound.wav"},
        { "KEYBOARD_TICK_SOUND",        "Music/KeyboardTick.wav"},
        { "ACHIEVEMENT_SOUND",          "Music/AchievementBell.wav"},

        /* CONFIG */
        { "CREDITS",                    "Config/Credits.txt"},

        /**/
        { "Background1",                "Map/Background1.png"},
        { "BG",                         "Map/BG.png"},
        { "Foreground",                 "Map/Foreground.png"},
        { "Middle",                     "Map/Middle.png"},
};

void GameConfig::init() {
    for(auto i : resource_table){
        m_asset_map.insert(std::make_pair(i.key, std::string(m_asset_base_dir) + "/" + i.value));
    }
}
