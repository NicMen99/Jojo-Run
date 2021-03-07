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

class AbsGameState;
class GameResourceManager;
class GameConfig;
class Factory;
class GameScene;
class GameStats;

#define GC Game::instance()->configManager()
#define RM Game::instance()->resourceManager()
#define GF Game::instance()->factory()
#define GS Game::instance()->gameScene()
#define STATS Game::instance()->gameStats()

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
    GameResourceManager & resourceManager() { return m_resourceManager; }
    Factory & factory() { return m_factory; }
    GameScene & gameScene() { return m_scene; }
    GameStats & gameStats() { return m_stats; }
private:
    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_clock;
    sf::Time m_accumulator = sf::Time::Zero;
    sf::Time m_framerate = sf::seconds(1.f/60.f);

private:
    AbsGameState* m_gameMachine;
    GameConfig& m_gameConfig;
    GameResourceManager& m_resourceManager;
    Factory& m_factory;
    GameScene& m_scene;
    GameStats& m_stats;

    /**/
private:

    ////////////////////
    std::ofstream file;
    int n;

    /////////////////


};

#endif //JOJO_RUN_GAME_H
