//
// Created by angiolo99 on 23/08/20.
//
#include <iostream>

#include "Game.h"


Game* Game::m_instance = nullptr;

Game* Game::instance() {
    if(nullptr == m_instance){
        m_instance = new Game;
        m_instance->init();
    }
    return m_instance;
}

Game* Game::instance(AbsGameState* fsm, GameConfig* cfg, ResourceManager* resm, Factory* fact, SceneManager* scn, GameStats* stats, ScoreManager* score) {
    if(nullptr == m_instance){
        m_instance = new Game(fsm, cfg, resm, fact, scn, stats, score);
        m_instance->init();
    }
    return m_instance;
}

void Game::deleteInstance() {
    if(m_instance!= nullptr){
        delete m_instance;
        m_instance= nullptr;
    }
}

Game::Game():
    m_gameMachine(new GameStateMachine(State::Init)),
    m_gameConfig(new GameConfig()),
    m_resourceManager(new ResourceManager()),
    m_factory(new Factory()),
    m_scene(new SceneManager()),
    m_stats(new GameStats()),
    m_score(new ScoreManager())
{
}

Game::Game(AbsGameState* fsm, GameConfig* cfg, ResourceManager* resm, Factory* fact, SceneManager* scn, GameStats* stats, ScoreManager* score):
        m_gameMachine(fsm),
        m_gameConfig(cfg),
        m_resourceManager(resm),
        m_factory(fact),
        m_scene(scn),
        m_stats(stats),
        m_score(score)
{

}

Game::~Game() {
    m_instance = nullptr;
};

void Game::init()
{
    m_gen.seed(m_rd());
    m_dist = std::uniform_int_distribution<int>(0,65535);
    m_gameConfig->init();
}

void Game::loop()
{
    m_window.create(sf::VideoMode(CONFIG->getWindowSize().x, CONFIG->getWindowSize().y), "JoJo Run");
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    while(m_window.isOpen()){
        while (m_window.pollEvent(m_event)) {
            if(m_event.type == sf::Event::Closed)
                m_window.close();
        }

        sf::Time elapsedTime = m_clock.restart();
        if(elapsedTime > sf::milliseconds(100)) {
#ifdef GAMEDEBUG
            std::cout << elapsedTime.asMilliseconds() << std::endl;
#endif
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

