//
// Created by Niccolo on 23/03/2021.
//
#include "Game.h"
#include "GameResourceManager.h"
#include "Animator.h"

void Animation::addFrame(const std::string & texture_name, sf::IntRect texture_rect, int8_t length, sf::Vector2u scale, bool flipx, bool flipy) {
    while (length-- > 0) {
        _addFrame(texture_name, texture_rect, scale, flipx, flipy);
    }
}

void Animation::_addFrame(const std::string & texture_name, sf::IntRect texture_rect, sf::Vector2u scale, bool flipx, bool flipy) {
    auto texture = RM.getTexture(texture_name);
    auto sprite = std::make_shared<sf::Sprite>();
    if(texture_rect == sf::IntRect {0,0,0,0}) {
        sprite->setTexture(*texture, true);
    }
    else {
        sprite->setTexture(*texture);
        sprite->setTextureRect(texture_rect);
    }

    float scalex = scale.x == 0 ? 1.0f : (float)scale.x/sprite->getLocalBounds().width;
    if(flipx) scalex = -scalex;
    float scaley = scale.y == 0 ? 1.0f : (float)scale.y/sprite->getLocalBounds().height;
    if(flipy) scaley = -scaley;
    if(scalex!=1 || scaley!=1)
        sprite->setScale(scalex, scaley);

    m_frames.emplace_back(std::make_pair(sprite, 1));
}

std::shared_ptr<sf::Sprite> Animation::update(int32_t delta_time) {
    return m_frames.at(m_count++%m_frames.size()).first;
}


void Animator::init() {

}

void Animator::update(int32_t delta_time) {
    m_sprite = m_animations[m_active_animation]->update(delta_time);
}

void Animator::play(const std::string & animation_name, int repetitions) {
    m_active_animation = animation_name;
    update(0);
}

bool Animator::done() const {
    auto animation = m_animations.find(m_active_animation);
    return animation != m_animations.end() ? animation->second->isDone() : false;
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

