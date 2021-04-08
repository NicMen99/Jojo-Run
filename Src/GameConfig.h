//
// Created by Niccolo on 05/10/2020.
//

#ifndef JOJO_RUN_GAMECONFIG_H
#define JOJO_RUN_GAMECONFIG_H

#include <SFML/System.hpp>

#include <string>
#include <map>

class GameConfig {
public:
    GameConfig();
    virtual ~GameConfig();
    void init();

    const sf::Vector2u & getWindowSize() const { return m_window_size; }
    const sf::Vector2f & getSceneSpeed() const { return m_scene_speed; }
    const sf::Vector2f & getGravity() const { return m_gravity; }
    float getHeroJumpForce() const { return m_hero_jumpForce; }
    int getHeroJumpMaxTime() const { return m_hero_jumpMaxTime; }
    float getHeroJumpSpeedLimit() const { return m_hero_jumpSpeedLimit; }
    float getHeroFallSpeedLimit() const { return m_hero_fallingSpeedLimit; }
    float getEnemyHitForce() const { return m_enemy_hitForce; }
    float getEnemyJumpSpeedLimit() const { return m_enemy_jumpSpeedLimit; }
    float getEnemyFallSpeedLimit() const { return m_enemy_fallingSpeedLimit; }
    float getKnifeSpeed() const { return m_knife_speed; }
    float getFireBulletSpeed() const { return m_fire_bullet_speed; }
    float getEmeraldBulletSpeed() const { return m_emerald_bullet_speed; }
    std::string getAssetPath(const std::string & name) const {
        auto it = m_asset_map.find(name);  return (it == m_asset_map.end()) ? "["+name+"]" : it->second; }

    /**/
    float getLevelDeltaH() const { return m_levelDelta_y; }
    float getBottomLevel() const { return m_base; }
    float getMiddleLevel() const { return m_middle; }
    float getTopLevel() const { return m_top; }

    /*Scene settings*/
protected:
    /* pixels */
    sf::Vector2u m_window_size = {1600,1000};
    /* pixels per secondo */
    sf::Vector2f m_scene_speed = {600.f, 0.f};
    /* delta pixels per secondo */
    sf::Vector2f m_gravity     = {0.f, 1500.f};

    /* delta pixels per secondo */
    float m_hero_jumpForce = m_gravity.y * 8.f;
    float m_enemy_hitForce = m_gravity.y * 500.f;
    /* millisecondi */
    int m_hero_jumpMaxTime = 400;
    /* pixels per secondo */
    float m_hero_jumpSpeedLimit = -750.f;
    float m_hero_fallingSpeedLimit = 1500.f;
    float m_enemy_jumpSpeedLimit = -500.f;
    float m_enemy_fallingSpeedLimit = 1000.f;
    float m_knife_speed = 1000.f;
    float m_fire_bullet_speed = 1200.f;
    float m_emerald_bullet_speed = 800.f;

    /* assets */
    const char * m_asset_base_dir = "Assets";
    std::map<std::string, std::string> m_asset_map;

    float m_levelDelta_y             = 300.f;
    float m_base                     = m_window_size.y-100.f;
    float m_middle                   = m_base - m_levelDelta_y;
    float m_top                      = m_middle - m_levelDelta_y;
};

#endif //JOJO_RUN_GAMECONFIG_H
