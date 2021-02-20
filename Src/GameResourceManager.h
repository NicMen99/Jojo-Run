//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_GAMERESOURCEMANAGER_H
#define JOJO_RUN_GAMERESOURCEMANAGER_H

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameResourceManager {
    GameResourceManager()=default;
    virtual ~GameResourceManager()=default;
    static GameResourceManager * _instance;
public:
    static GameResourceManager * instance();

    sf::Texture* getTexture(const std::string & texture);
    sf::SoundBuffer* getSound(const std::string & sound);

private:
    std::map<std::string, sf::Texture> m_texture_map;
    std::map<std::string, sf::SoundBuffer> m_sound_map;
    std::map<std::string, sf::Font> m_font_map;

};

#define RM GameResourceManager::instance()

#endif //JOJO_RUN_GAMERESOURCEMANAGER_H
