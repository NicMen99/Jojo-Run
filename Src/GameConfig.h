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

    const sf::Vector2u &getWindowSize() const {return m_window_size;}
    const sf::Vector2f &getSceneSpeed() const {return m_scene_speed;}
    float getGroundYpos() const {return m_groundYpos;}

private:

private:
    // int loadConfigFile(std::string s);
    std::string asset_base_dir;
    std::map<std::string, std::string> asset_map;

private:
    const sf::Vector2u m_window_size = {1600,1000};
    const sf::Vector2f m_scene_speed = {200, 0};   // pixels x second
    const float m_groundYpos = 63.0f;
};

#endif //JOJO_RUN_GAMECONFIG_H
