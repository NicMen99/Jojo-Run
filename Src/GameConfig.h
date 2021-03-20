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
    GameConfig()=default;
    virtual ~GameConfig()=default;
    void init();

    const sf::Vector2u & getWindowSize() const { return m_window_size; }
    const sf::Vector2f & getSceneSpeed() const { return m_scene_speed; }
    const sf::Vector2f & getGravity() const { return m_gravity; }

    const std::string getAssetPath(const std::string & name) const {
        auto it = m_asset_map.find(name);  return (it == m_asset_map.end()) ? "" : it->second; }

    /**/
    float getMBase() const { return m_base; }
    float getMMiddle() const { return m_middle; }
    float getMTop() const { return m_top; }
    float getGroundYpos() const { return m_groundYpos; }

private:
    /* pixels */
    const sf::Vector2u m_window_size = {1600,1000};
    /* pixels per secondo */
    const sf::Vector2f m_scene_speed = {400.f, 0.f};
    /* delta pixels per secondo */
    const sf::Vector2f m_gravity     = {0.f, 1500.f};

    /* assets */
    const char * m_asset_base_dir = "Assets";
    std::map<std::string, std::string> m_asset_map;

    const float m_groundYpos         = 63.0f;
    float m_levelDelta_y             = 300.f;
    float m_base                     = m_window_size.y-100.f;
    float m_middle                   = m_base - m_levelDelta_y;
    float m_top                      = m_middle - m_levelDelta_y;
};

#endif //JOJO_RUN_GAMECONFIG_H
