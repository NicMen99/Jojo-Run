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
    GS.init();

    /*
    fireEnemyBuffer.loadFromFile(GC.getAssetPath("fireEnemyShout"));
    m_context->fireEnemySound.setBuffer(fireEnemyBuffer);
    m_context->fireEnemySound.setVolume(21.f);

    emeraldEnemyBuffer.loadFromFile(GC.getAssetPath("emeraldEnemyShout"));
    m_context->emeraldEnemySound.setBuffer(emeraldEnemyBuffer);
    m_context->emeraldEnemySound.setVolume(21.f);

    hamonEnemyBuffer.loadFromFile(GC.getAssetPath("hamonEnemyShout"));
    m_context->hamonEnemySound.setBuffer(hamonEnemyBuffer);
    m_context->hamonEnemySound.setVolume(21.f);

    // Loading Font
    m_context->font.loadFromFile(GC.getAssetPath("arcadeclassic"));

    m_context->gameMusic.openFromFile(GC.getAssetPath("soundTrack"));
    m_context->gameMusic.setLoop(true);
    m_context->gameMusic.setVolume(10.f);
    */
}

void PlayState::onEnter() {
    /*
    m_context->gameMusic.play();
     */
}

void PlayState::onExit() {
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

