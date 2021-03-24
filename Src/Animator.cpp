//
// Created by Niccolo on 23/03/2021.
//

#include "Animator.h"

Animator::Animator(sf::Sprite &mSprite) :
    m_sprite(mSprite) {

}

void Animator::init() {

}

void Animator::update(int32_t delta_time) {

}

void Animator::playAnimation(const std::string & id, int repetitions) {

}

bool Animator::animationDone() const {
    auto animation = m_animations.find(m_active_animation);
    return animation != m_animations.end() ? animation->second.isDone() : false;
}
