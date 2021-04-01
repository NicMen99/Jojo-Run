//
// Created by Niccolo on 30/03/2021.
//

#ifndef JOJO_RUN_SOUNDMANAGER_H
#define JOJO_RUN_SOUNDMANAGER_H


#include <string>
#include <map>
#include <SFML/Audio.hpp>


class SoundManager {
public:
    SoundManager();
    virtual ~SoundManager();

    void addSound(const std::string & sound_name, const std::string & sound_resource);
    void playSound(const std::string & sound_name, float volume = 100.f);

private:
    sf::Sound m_sound;
    std::string m_active_sound;
    std::map<std::string, std::string> m_sound_map;
};


#endif //JOJO_RUN_SOUNDMANAGER_H
