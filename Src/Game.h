//
// Created by angiolo99 on 23/08/20.
//

#ifndef JOJO_RUN_GAME_H
#define JOJO_RUN_GAME_H

#include <list>
#include <string>
#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "StateMachine/GameStateMachine.h"
#include "GameConfig.h"
#include "GameStats.h"
#include "ResourceManager.h"
#include "Factory.h"
#include "SceneManager.h"
#include "ScoreManager.h"

#define CONFIG Game::instance()->configManager()
#define RESOURCE Game::instance()->resourceManager()
#define FACTORY Game::instance()->factory()
#define SCENE Game::instance()->gameScene()
#define STATS Game::instance()->gameStats()
#define SCORE Game::instance()->gameScore()
#define RAND Game::instance()->rand


class Game
{
    static Game* m_instance;
    Game();
public:
    static Game* instance();
    ~Game();

public:
    void init();
    void loop();

    GameConfig & configManager() { return m_gameConfig; }
    ResourceManager & resourceManager() { return m_resourceManager; }
    Factory & factory() { return m_factory; }
    SceneManager & gameScene() { return m_scene; }
    GameStats & gameStats() { return m_stats; }
    ScoreManager & gameScore() { return m_score; }
    int rand(int max) { std::uniform_int_distribution<int> d(0, max - 1); return d(m_gen);}

private:
    sf::RenderWindow m_window;
    sf::Event m_event{};
    sf::Clock m_clock;
    sf::Time m_accumulator = sf::Time::Zero;
    sf::Time m_framerate = sf::seconds(1.f/60.f);

private:
    AbsGameState* m_gameMachine;
    GameConfig& m_gameConfig;
    ResourceManager& m_resourceManager;
    Factory& m_factory;
    SceneManager& m_scene;
    GameStats& m_stats;
    ScoreManager& m_score;

    std::random_device m_rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 m_gen; //Standard mersenne_twister_engine seeded with rd()
};

#endif //JOJO_RUN_GAME_H
