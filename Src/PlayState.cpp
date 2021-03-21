//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "GameScene.h"
#include "GameConfig.h"
#include "PlayState.h"

PlayState* PlayState::m_instance = nullptr;

PlayState* PlayState::instance() {
    if(nullptr == m_instance){
        m_instance = new PlayState;
        m_instance->init();
    }
    return m_instance;
}

void PlayState::init() {
    m_music.openFromFile(GC.getAssetPath("soundTrack"));
}

void PlayState::onEnter() {
    GS.init();
    m_music.play();
}

void PlayState::onExit() {
    m_music.stop();
}

void PlayState::update(int32_t delta_time) {
    if(GS.levelend()) {
        changeState(State::Over);
    }
    GS.update(delta_time);
}

void PlayState::render(sf::RenderWindow& window) {
    GS.render(window);
}

