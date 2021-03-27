//
// Created by Niccolo on 17/02/2021.
//

#include "InitState.h"

InitState* InitState::m_instance = nullptr;

InitState* InitState::instance() {
    if(nullptr == m_instance){
        m_instance = new InitState();
        m_instance->init();
    }
    return m_instance;
}

void InitState::onEnter() {
    changeState(State::Menu);
}
