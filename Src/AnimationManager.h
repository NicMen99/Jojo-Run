//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_ANIMATIONMANAGER_H
#define JOJO_RUN_ANIMATIONMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

struct FrameParams {
    FrameParams(int c, const char * n, const sf::IntRect& r, const sf::Vector2u& s, const sf::Vector2<bool>& f) :
            count(c), texture_name(n), texture_rect(r), scale(s), flip(f) {}
    int               count;
    std::string       texture_name{};
    sf::IntRect       texture_rect;
    sf::Vector2u      scale;
    sf::Vector2<bool> flip;
};

class Animation {
public:
    explicit Animation(std::string  name);
    virtual ~Animation();
    const std::string & name() { return m_name; }
    unsigned int total_frames() const { return m_frames.size(); }
    void addFrame(const FrameParams & frame_params);
    bool isDone() const { return m_count >= total_frames(); }
    std::shared_ptr<sf::Sprite> update(int32_t delta_time);
    void reset(bool loop) { m_loop=loop; m_count = 0; }

private:
    std::string m_name;
    bool m_loop = false;
    unsigned int m_count = 0;
    std::vector< std::pair< std::shared_ptr<sf::Sprite>, uint32_t> > m_frames;
};

class AnimationManager {
public:
    AnimationManager();
    virtual ~AnimationManager();

    bool isCurrentAnimation(const std::string & animation_name);
    void addAnimation(const std::string & animation_name, const std::list<FrameParams>& frames);
    void update(int32_t delta_time);

    void play(const std::string & animation_name, bool loop=false);
    bool done() const;
    std::shared_ptr<sf::Sprite> getCurrentFrame();
    std::shared_ptr<sf::Sprite> getCurrentFrame() const;

private:
    std::shared_ptr<Animation> createAnimation(const std::string & animation_name);

    std::shared_ptr<sf::Sprite> m_current_sprite;
    std::shared_ptr<Animation> m_current_animation;
    std::map<std::string, std::shared_ptr<Animation>> m_animations;
};


#endif //JOJO_RUN_ANIMATIONMANAGER_H
