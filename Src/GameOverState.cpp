//
// Created by Niccolo on 15/02/2021.
//

#include "GameOverState.h"

GameOverState* GameOverState::m_instance = nullptr;

void GameOverState::onEnter() {
}

void GameOverState::onExit() {
}

void GameOverState::update() {

}

void GameOverState::render() {

}

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}
