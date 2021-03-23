//
// Created by angiolo99 on 23/08/20.
//
#include <iostream>

#include "GameStateMachine.h"
#include "GameConfig.h"
#include "GameResourceManager.h"
#include "GameScene.h"
#include "GameStats.h"
#include "Factory.h"
#include "Game.h"

#define DEBUG

Game* Game::m_instance = nullptr;

Game* Game::instance() {
    if(nullptr == m_instance){
        m_instance = new Game;
        m_instance->init();
    }
    return m_instance;
}

Game::Game():
    m_gameMachine(new GameStateMachine(State::Init)),
    m_gameConfig(*new GameConfig()),
    m_resourceManager(*new GameResourceManager()),
    m_factory(*new Factory()),
    m_scene(*new GameScene()),
    m_stats(*new GameStats())
{
}

Game::~Game() = default;

void Game::init()
{
    m_gen.seed(m_rd());
    m_gameConfig.init();
}

void Game::loop()
{
    m_window.create(sf::VideoMode(GC.getWindowSize().x, GC.getWindowSize().y), "JoJo Run");
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    while(m_window.isOpen()){
        while (m_window.pollEvent(m_event)) {
            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }

        sf::Time elapsedTime = m_clock.restart();
#ifdef DEBUG
        if(elapsedTime > sf::milliseconds(50)) {
            elapsedTime = sf::milliseconds(50);
        }
#endif
        m_accumulator += elapsedTime;

        while (m_accumulator > m_framerate) {
            m_accumulator -= m_framerate;
            m_gameMachine->exec();
            m_gameMachine->update(m_framerate.asMilliseconds());
            sf::sleep(sf::milliseconds(10));
        }

        m_window.clear();
        m_gameMachine->render(m_window);
        m_window.display();
    }
}

