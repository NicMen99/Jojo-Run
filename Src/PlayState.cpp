//
// Created by Niccolo on 15/02/2021.
//

#include "PlayState.h"
#include "Game.h"

/**/
#include "Background.h"
#include "GameConfig.h"
#include "GameResourceManager.h"
#include "Hero.h"

PlayState* PlayState::m_instance = nullptr;

Background background1, background2, background3, background4;

sf::SoundBuffer collisionBuffer;
sf::SoundBuffer powerUpBuffer;
sf::SoundBuffer shieldOnBuffer;
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
    sf::Vector2u window_size = m_context->getWindowSize();

    background1.init("Background1", true, {7.4, 7.4});
    background2.init("BG", true, {7.4, 7.4});
    background3.init("Foreground", true, {7.4, 7.4});
    background4.init("Middle", true, {7.4, 7.4});

    m_context->heroTexture1.loadFromFile(GC->getAssetPath("playerTexture"));
    m_context->heroTexture2.loadFromFile(GC->getAssetPath("playerTextureUp"));
    m_context->hero.setHeroTexture(m_context->heroTexture1);
    m_context->heroTextureS1.loadFromFile(GC->getAssetPath("playerShieldTexture"));

    collisionBuffer.loadFromFile(GC->getAssetPath("collisionSound"));
    m_context->collisionSound.setBuffer(collisionBuffer);
    m_context->collisionSound.setVolume(22.f);

    powerUpBuffer.loadFromFile(GC->getAssetPath("shieldSound"));
    m_context->powerUpSound.setBuffer(powerUpBuffer);
    m_context->powerUpSound.setVolume(20.f);

    shieldOnBuffer.loadFromFile(GC->getAssetPath("shieldOn"));
    m_context->shieldOnSound.setBuffer(shieldOnBuffer);
    m_context->shieldOnSound.setVolume(20.f);

    fireEnemyBuffer.loadFromFile(GC->getAssetPath("fireEnemyShout"));
    m_context->fireEnemySound.setBuffer(fireEnemyBuffer);
    m_context->fireEnemySound.setVolume(21.f);

    emeraldEnemyBuffer.loadFromFile(GC->getAssetPath("emeraldEnemyShout"));
    m_context->emeraldEnemySound.setBuffer(emeraldEnemyBuffer);
    m_context->emeraldEnemySound.setVolume(21.f);

    hamonEnemyBuffer.loadFromFile(GC->getAssetPath("hamonEnemyShout"));
    m_context->hamonEnemySound.setBuffer(hamonEnemyBuffer);
    m_context->hamonEnemySound.setVolume(21.f);

    // Loading Font
    m_context->font.loadFromFile(GC->getAssetPath("arcadeclassic"));

    m_context->gameMusic.openFromFile(GC->getAssetPath("soundTrack"));
    m_context->gameMusic.setLoop(true);
    m_context->gameMusic.setVolume(10.f);

}

void PlayState::onEnter() {
    m_context->gameMusic.play();
}

void PlayState::onExit() {
}

void PlayState::update() {
    background1.update(sf::Vector2f(-m_context->getSpeed().x * 1.2, 0));
    background2.update(sf::Vector2f(-m_context->getSpeed().x, 0));
    background3.update(sf::Vector2f(-m_context->getSpeed().x*1.6, 0));
    background4.update(sf::Vector2f(-m_context->getSpeed().x*1.4, 0));

    if (m_context->hero.getIsDead() && m_context->txtCount == 0){
        changeState(State::Over);
    }

    m_context->createObj();
    m_context->createEnemy();
    m_context->moveObject();
    m_context->moveHero();
    m_context->throwKnife();
    m_context->moveEnemy();
    m_context->deleteObject();
    m_context->deleteEnemy();
    m_context->handleTxt();

    m_context->setScore(m_context->score);
    m_context->setHealth(m_context->getHealth());

    if (!m_context->hero.getIsDead()) {
        m_context->collision();
    }
    if (m_context->getIsCollided()) {
        if (m_context->collisionClk.getElapsedTime().asSeconds() >= 0) {
            if(m_context->getIsFirewallCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else{
                    m_context->hero.setHealth(m_context->hero.getHealth() - 15);
                    m_context->notify();
                }
                m_context->firewalls.erase(m_context->firewalls.begin() + m_context->collidedfirewalls);
                m_context->setFirewallCollision(false);
                m_context->hero.gameOver();
            }
            if(m_context->getIsBlockCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else{
                    m_context->hero.setHealth(m_context->hero.getHealth() - 70);
                    m_context->notify();
                }
                m_context->blocks.erase(m_context->blocks.begin() + m_context->collidedblocks);
                m_context->setBlockCollision(false);
                m_context->hero.gameOver();
            }
            if(m_context->getIsEnemyCollision()){
                if(m_context->getIsShieldOn()){
                    m_context->setIsShieldOn(false);
                }
                else {
                    m_context->hero.setHealth(m_context->hero.getHealth() - 90);
                    m_context->notify();
                }
                m_context->enemies.erase(m_context->enemies.begin() + m_context->collidedenemies);
                m_context->setEnemyCollision(false);
                m_context->hero.gameOver();
            }
            if(m_context->getIsShieldCollision()){
                m_context->setIsShieldOn(true);
                m_context->hero.setTexture(m_context->heroTextureS1);
                m_context->powerups.erase(m_context->powerups.begin()+m_context->collidedpowerups);
                m_context->notify();
                m_context->setShieldPowerupCollision(false);
            }
            if(m_context->getIsKnifeThrownCollision()){
                //se l'eroe colpisce un nemico col coltello lanciato, la sua vita aumenta leggermente
                m_context->hero.setHealth(m_context->hero.getHealth() + 20);
                m_context->notify();
                m_context->knives.erase(m_context->knives.begin() + m_context->collidedknives);
                m_context->enemies.erase(m_context->enemies.begin() + m_context->collidedenemies);
                m_context->setKnifeCollision(false);
            }
            if(m_context->getIsKnifeCollision()){
                m_context->hero.setKnives(m_context->hero.getKnives() + 4);
                m_context->notify();
                m_context->powerups.erase(m_context->powerups.begin()+m_context->collidedknives);
                m_context->setKnivesPowerupCollision(false);
            }
        }
        m_context->setIsCollided(false);
    }

    if(m_context->getIsShieldOn() && m_context->shieldClk.getElapsedTime().asSeconds() >= 15.f) {
        m_context->setIsShieldOn(false);
        m_context->hero.setHeroTexture(m_context->heroTexture1);
    }

    if (m_context->scoreClk.getElapsedTime().asSeconds() >= 1.f && !m_context->hero.getIsDead()) {
        m_context->score ++;
        m_context->scoreClk.restart();
        m_context->notify();
    }
}

void PlayState::render(sf::RenderWindow& window) {
    background2.render(window);
    background1.render(window);
    background4.render(window);
    background3.render(window);

    m_context->hero.renderHero(window);
    for (auto &block : m_context->blocks)
        window.draw(*block);
    for (auto &movBlock : m_context->blocks)
        window.draw(*movBlock);
    for (auto &power : m_context->powerups)
        window.draw(*power);
    for (auto &enem : m_context->enemies)
        window.draw(*enem);
    for (auto &movEnem : m_context->enemies)
        window.draw(*movEnem);
    for (auto &fire: m_context->firewalls)
        window.draw(*fire);
    for (auto &movFire: m_context->firewalls)
        window.draw(*movFire);
    for (auto &knife : m_context->knives)
        window.draw(*knife);
    window.draw(m_context->scoreTxt);
    window.draw(m_context->numScore);
    window.draw(m_context->lifeTxt);
    window.draw(m_context->numLife);
    window.draw(m_context->knivesTxt);
    window.draw(m_context->numKnives);
}

