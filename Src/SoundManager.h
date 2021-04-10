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

    void clear();

    void addSound(const std::string & sound_name, const std::string & sound_resource);
    void playSound(const std::string & sound_name, float volume = 100.f);
    void playMusic(const std::string & sound_name = "", float volume = 100.f, float pitch = 1.f);
    void setVolume(float volume);
    void setPitch(float pitch);
    void stopMusic();

private:
    sf::Sound m_sound;
    std::string m_active_sound;
    std::map<std::string, std::string> m_sound_map;
    sf::Music m_music;
};


#endif //JOJO_RUN_SOUNDMANAGER_H
