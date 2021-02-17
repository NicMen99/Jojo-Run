//
// Created by Niccolo on 15/02/2021.
//

#include "PlayState.h"

PlayState* PlayState::m_instance = nullptr;

void PlayState::onEnter() {
}

void PlayState::onExit() {
}

void PlayState::update() {
}

void PlayState::render() {

}

PlayState* PlayState::instance() {
    if(nullptr == m_instance){
        m_instance = new PlayState;
        m_instance->init();
    }
    return m_instance;
}
