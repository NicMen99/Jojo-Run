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
    float getHeroJumpForce() const { return m_jumpForce; }
    int getHeroJumpMaxTime() const { return m_jumpMaxTime; }
    float getHeroJumpSpeedLimit() const { return m_jumpSpeedLimit; }
    float getHeroFallSpeedLimit() const { return m_fallingSpeedLimit; }

    std::string getAssetPath(const std::string & name) const {
        auto it = m_asset_map.find(name);  return (it == m_asset_map.end()) ? "["+name+"]" : it->second; }

    /**/
    float getBottomLevel() const { return m_base; }
    float getMiddleLevel() const { return m_middle; }
    float getTopLevel() const { return m_top; }

    /*Scene settings*/
protected:
    /* pixels */
    sf::Vector2u m_window_size = {1600,1000};
    /* pixels per secondo */
    sf::Vector2f m_scene_speed = {450.f, 0.f};
    /* delta pixels per secondo */
    sf::Vector2f m_gravity     = {0.f, 1500.f};

    /* delta pixels per secondo */
    float m_jumpForce = m_gravity.y * 3;
    /* millisecondi */
    int m_jumpMaxTime = 250;
    /* pixels per secondo */
    float m_jumpSpeedLimit = -750.f;
    float m_fallingSpeedLimit = 1500.f;

    /* assets */
    const char * m_asset_base_dir = "Assets";
    std::map<std::string, std::string> m_asset_map;

    float m_levelDelta_y             = 300.f;
    float m_base                     = m_window_size.y-100.f;
    float m_middle                   = m_base - m_levelDelta_y;
    float m_top                      = m_middle - m_levelDelta_y;
};

#endif //JOJO_RUN_GAMECONFIG_H
