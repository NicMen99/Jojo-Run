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


class Game {

public:
    static Game* instance();
    static Game* instance(AbsGameState* fsm, GameConfig* cfg, ResourceManager* resm, Factory* fact, SceneManager* scn, GameStats* stats, ScoreManager* score);
    ~Game();

    void init();
    void loop();

    GameConfig * configManager() { return m_gameConfig.get(); }
    ResourceManager * resourceManager() { return m_resourceManager.get(); }
    Factory * factory() { return m_factory.get(); }
    SceneManager * gameScene() { return m_scene.get(); }
    GameStats * gameStats() { return m_stats.get(); }
    ScoreManager * gameScore() { return m_score.get(); }
    int rand(int max) { std::uniform_int_distribution<int> d(0, max - 1); return d(m_gen);}

private:

    static Game* m_instance;
    Game();
    Game(AbsGameState* fsm, GameConfig* cfg, ResourceManager* resm, Factory* fact, SceneManager* scn, GameStats* stats, ScoreManager* score); //test function

    sf::RenderWindow m_window;
    sf::Event m_event{};
    sf::Clock m_clock;
    sf::Time m_accumulator = sf::Time::Zero;
    sf::Time m_framerate = sf::seconds(1.f/60.f);

    std::unique_ptr<AbsGameState> m_gameMachine;
    std::unique_ptr<GameConfig> m_gameConfig;
    std::unique_ptr<ResourceManager> m_resourceManager;
    std::unique_ptr<Factory> m_factory;
    std::unique_ptr<SceneManager> m_scene;
    std::unique_ptr<GameStats> m_stats;
    std::unique_ptr<ScoreManager> m_score;

    std::random_device m_rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 m_gen; //Standard mersenne_twister_engine seeded with rd()
};

#endif //JOJO_RUN_GAME_H
