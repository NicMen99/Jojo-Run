//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "GameScene.h"
#include "inputManager.h"
#include "GameConfig.h"
#include "PlayState.h"
#include "Hero.h"

PlayState* PlayState::m_instance = nullptr;

sf::SoundBuffer fireEnemyBuffer;
sf::SoundBuffer emeraldEnemyBuffer;
sf::SoundBuffer hamonEnemyBuffer;

const float ground = 63.0f;

PlayState* PlayState::instance() {
    if(nullptr == m_instance){
        m_instance = new PlayState;
        m_instance->init();
    }
    return m_instance;
}

void PlayState::init() {
    GS.init();
    IM.init();
    HERO.init();

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

}

void PlayState::onEnter() {
    m_context->gameMusic.play();
}

void PlayState::onExit() {
}

void PlayState::update(int32_t delta_time) {
    GS.update(delta_time);
    HERO.update(delta_time);

    if (HERO.getIsDead() && m_context->txtCount == 0){
        changeState(State::Over);
    }

    for (auto &knife : m_context->knives)
        knife->update(delta_time);
    m_context->handleTxt();

    m_context->setScore(m_context->score);
    m_context->setHealth(m_context->getHealth());

    // Collision
    if (!HERO.getIsDead()) {
        m_context->collision();
    }
    if (m_context->getIsCollided()) {
        if (m_context->collisionClk.getElapsedTime().asSeconds() >= 0) {
            if(m_context->getIsFirewallCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else{
                    HERO.setHealth(HERO.getHealth() - 1);
                    m_context->notify();
                }
                m_context->setFirewallCollision(false);
                HERO.gameOver();
            }
            if(m_context->getIsBlockCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else {
                    HERO.setHealth(HERO.getHealth() - 70);
                    m_context->notify();
                }
                GS.m_obstacles.erase(GS.m_obstacles.begin() + m_context->collidedblocks);
                m_context->setBlockCollision(false);
                HERO.gameOver();
            }
            if(m_context->getIsEnemyCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else {
                    HERO.setHealth(HERO.getHealth() - 90);
                    m_context->notify();
                }
                GS.m_enemies.erase(GS.m_enemies.begin() + m_context->collidedenemies);
                m_context->setEnemyCollision(false);
                HERO.gameOver();
            }
            if(m_context->getIsShieldCollision()){
                m_context->setIsShieldOn(true);
                HERO.setShieldOn();
                GS.m_powerups.erase(GS.m_powerups.begin()+m_context->collidedpowerups);
                m_context->notify();
                m_context->setShieldPowerupCollision(false);
            }
            if(m_context->getIsKnifeThrownCollision()){
                //se l'eroe colpisce un nemico col coltello lanciato, la sua vita aumenta leggermente
                HERO.setHealth(HERO.getHealth() + 20);
                m_context->notify();
                m_context->knives.erase(m_context->knives.begin() + m_context->collidedknives);
                GS.m_enemies.erase(GS.m_enemies.begin() + m_context->collidedenemies);
                m_context->setKnifeCollision(false);
            }
            if(m_context->getIsKnifeCollision()){
                HERO.setKnives(HERO.getKnives() + 4);
                m_context->notify();
                GS.m_powerups.erase(GS.m_powerups.begin()+m_context->collidedknives);
                m_context->setKnivesPowerupCollision(false);
            }
        }
        m_context->setIsCollided(false);
    }

    if(m_context->getIsShieldOn() && m_context->shieldClk.getElapsedTime().asSeconds() >= 15.f) {
        m_context->setIsShieldOn(false);
        HERO.setStanding();
    }

    if (m_context->scoreClk.getElapsedTime().asSeconds() >= 1.f && !HERO.getIsDead()) {
        m_context->score ++;
        m_context->scoreClk.restart();
        m_context->notify();
    }
}

void PlayState::render(sf::RenderWindow& window) {
    GS.render(window);
    HERO.render(window);
    for (auto &knife : m_context->knives)
        knife->render(window);
    window.draw(m_context->scoreTxt);
    window.draw(m_context->numScore);
    window.draw(m_context->lifeTxt);
    window.draw(m_context->numLife);
    window.draw(m_context->knivesTxt);
    window.draw(m_context->numKnives);
}

