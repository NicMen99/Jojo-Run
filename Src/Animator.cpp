//
// Created by Niccolo on 23/03/2021.
//
#include "Game.h"
#include "ResourceManager.h"
#include "Animator.h"

void Animation::addFrame(const FrameParams & frame_params) {
    uint8_t count = frame_params.count;
    while (count-- >0) {
        auto sprite = std::make_shared<sf::Sprite>();

        auto texture = RESOURCE.getTexture(frame_params.texture_name);
        if(frame_params.texture_rect == sf::IntRect{0,0,0,0}) {
            sprite->setTexture(*texture, true);
        }
        else {
            sprite->setTexture(*texture);
            sprite->setTextureRect(frame_params.texture_rect);
        }

        float scalex = frame_params.scale.x == 0 ? 1.0f : (float)frame_params.scale.x/sprite->getLocalBounds().width;
        if(frame_params.flip.x) scalex = -scalex;
        float scaley = frame_params.scale.y == 0 ? 1.0f : (float)frame_params.scale.y/sprite->getLocalBounds().height;
        if(frame_params.flip.y) scaley = -scaley;
        if(scalex!=1 || scaley!=1)
            sprite->setScale(scalex, scaley);

        sprite->setOrigin(frame_params.flip.x?sprite->getLocalBounds().width:0,
                          frame_params.flip.y?sprite->getLocalBounds().height:0);

        m_frames.emplace_back(std::make_pair(sprite, 1));
    }
}

Animator::Animator() :
    m_current_sprite(std::make_shared<sf::Sprite>()),
    m_current_animation(nullptr) {

}

std::shared_ptr<sf::Sprite> Animation::update(int32_t delta_time) {
    if(total_frames() == 0) return nullptr;
    return m_frames.at(m_count++%m_frames.size()).first;
}


void Animator::update(int32_t delta_time) {
    if(m_current_animation != nullptr) {
        std::shared_ptr<sf::Sprite> animation = m_current_animation->update(delta_time);
        if(animation != nullptr)
            m_current_sprite = m_current_animation->update(delta_time);
    }
}

void Animator::play(const std::string & animation_name, int repetitions) {
    auto it = m_animations.find(animation_name);
    if(it != m_animations.end()) {
        m_current_animation = it->second;
        update(0);
    }
}

bool Animator::done() const {
    return m_current_animation == nullptr || m_current_animation->isDone();
}

std::shared_ptr<sf::Sprite> Animator::getCurrentFrame() {
    return m_current_sprite;
}

std::shared_ptr<sf::Sprite> Animator::getCurrentFrame() const {
    return m_current_sprite;
}

void Animator::addAnimation(const std::string & animation_name, const std::list<Animation::FrameParams>& frames) {
    auto animation = createAnimation(animation_name);
    for(const auto& frame : frames) {
        animation->addFrame(frame);
    }
    if(m_animations.size()==1) {
        play(animation_name, 0);
    }
}

std::shared_ptr<Animation> Animator::createAnimation(const std::string & animation_name) {
    auto it = m_animations.find(animation_name);
    if(it != m_animations.end()) {
        return it->second;
    }
    std::shared_ptr<Animation> animation = std::make_shared<Animation>();
    m_animations.insert(std::make_pair(animation_name, animation));
    return animation;
}
