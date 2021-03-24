//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_ANIMATOR_H
#define JOJO_RUN_ANIMATOR_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Animation {
public:
    bool isDone() const { return m_count > m_frames.size(); }
private:
    unsigned int m_count = 0;
    std::vector<sf::Sprite> m_frames;
};

class Animator {
public:
    explicit Animator(sf::Sprite & sprite);
    virtual ~Animator() = default;

    void init();
    void update(int32_t delta_time);

    void playAnimation(const std::string & id, int repetitions=-1);
    bool animationDone() const;

private:
    sf::Sprite & m_sprite;
    std::string m_active_animation;
    std::map<std::string, Animation&> m_animations;
};


#endif //JOJO_RUN_ANIMATOR_H
