//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_ANIMATOR_H
#define JOJO_RUN_ANIMATOR_H

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Animation {
public:
    void addFrame(const std::string & texture_name,
                  sf::IntRect texture_rect={0,0,0,0},
                  int8_t length=1,
                  sf::Vector2u scale = {0,0},
                  bool flipx = false,
                  bool flipy = false);
    bool isDone() const { return m_count > m_frames.size(); }
    std::shared_ptr<sf::Sprite> update(int32_t delta_time);
private:
    void _addFrame(const std::string & texture_name,
                  sf::IntRect texture_rect={0,0,0,0},
                  sf::Vector2u scale = {0,0},
                  bool flipx = false,
                  bool flipy = false);
    unsigned int m_count = 0;
    std::vector< std::pair< std::shared_ptr<sf::Sprite>, uint32_t> > m_frames;
};

class Animator {
public:
    Animator() = default;
    virtual ~Animator() = default;

    void init();
    void update(int32_t delta_time);
    std::shared_ptr<sf::Sprite> getCurrentFrame() { return m_sprite; }
    std::shared_ptr<sf::Sprite> getCurrentFrame() const { return m_sprite; }

    void play(const std::string & animation_name = "DEFAULT", int repetitions= -1);
    bool done() const;

    std::shared_ptr<Animation> createAnimation(const std::string & animation_name = "DEFAULT");

private:
    std::shared_ptr<sf::Sprite> m_sprite;
    std::string m_active_animation;
    std::map<std::string, std::shared_ptr<Animation>> m_animations;
};


#endif //JOJO_RUN_ANIMATOR_H
