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

    void init(const std::string & base_dir);
    std::string getAssetPath(const std::string & name);
    float getMBase() const;
    float getMMiddle() const;
    float getMTop() const;

    const sf::Vector2u & getWindowSize() const {return m_window_size;}
    const sf::Vector2f & getSceneSpeed() const {return m_scene_speed;}
    const sf::Vector2f & getGravity() const { return m_gravity; }
    float getGroundYpos() const {return m_groundYpos;}

private:
    // int loadConfigFile(std::string s);
    std::string asset_base_dir;
    std::map<std::string, std::string> asset_map;

    float m_levelDelta_y = 300.f;
    float m_base;
    float m_middle;
    float m_top;

private:
    const sf::Vector2u m_window_size = {1600,1000};
    const sf::Vector2f m_scene_speed = {400.f, 0.f};    // pixels x secondo
    const sf::Vector2f m_gravity = {0.f, 500.f};        // delta pixels x secondo
    const float m_groundYpos = 63.0f;
};

#endif //JOJO_RUN_GAMECONFIG_H
