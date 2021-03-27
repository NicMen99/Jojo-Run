//
// Created by Niccolo on 20/02/2021.
//

#ifndef JOJO_RUN_RESOURCEMANAGER_H
#define JOJO_RUN_RESOURCEMANAGER_H

#include <memory>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager
{
public:
    ResourceManager()=default;
    virtual ~ResourceManager()=default;

    std::shared_ptr<sf::Texture> getTexture(const std::string & texture);
    std::shared_ptr<sf::SoundBuffer> getSound(const std::string & sound);
    std::shared_ptr<sf::Font> getFont(const std::string & font);

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> m_texture_map;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_sound_map;
    std::map<std::string, std::shared_ptr<sf::Font>> m_font_map;
};

#endif //JOJO_RUN_RESOURCEMANAGER_H
