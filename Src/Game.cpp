//
// Created by angiolo99 on 23/08/20.
//
#include <iostream>

#include "StateMachine/GameStateMachine.h"
#include "GameConfig.h"
#include "ResourceManager.h"
#include "Factory.h"
#include "SceneManager.h"
#include "GameStats.h"
#include "Entity.h"
#include "ScoreHUD.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "Game.h"


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
    m_resourceManager(*new ResourceManager()),
    m_factory(*new Factory()),
    m_scene(*new SceneManager()),
    m_stats(*new GameStats()),
    m_score(*new ScoreManager())
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
    m_window.create(sf::VideoMode(CONFIG.getWindowSize().x, CONFIG.getWindowSize().y), "JoJo Run");
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    while(m_window.isOpen()){
        while (m_window.pollEvent(m_event)) {
            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }

        sf::Time elapsedTime = m_clock.restart();
        if(elapsedTime > sf::milliseconds(100)) {
            std::cout << elapsedTime.asMilliseconds() << std::endl;
            elapsedTime = sf::milliseconds(100);
        }
        m_accumulator += elapsedTime;

        while (m_accumulator > m_framerate) {
            m_accumulator -= m_framerate;
            m_gameMachine->exec();
            m_gameMachine->update(m_framerate.asMilliseconds());
            // sf::sleep(sf::milliseconds(1));
        }

        m_window.clear(sf::Color::Black);
        m_gameMachine->render(m_window);
        m_window.display();
    }
}

