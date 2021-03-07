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

#include "Subject.h"

class AbsGameState;
class GameResourceManager;
class GameConfig;
class Factory;
class GameScene;
class Observer;

#define GC Game::instance()->configManager()
#define RM Game::instance()->resourceManager()
#define GF Game::instance()->factory()
#define GS Game::instance()->gameScene()

class Game: public Subject
{
    static Game* m_instance;
    Game();
public:
    static Game* instance();
    ~Game() override;

public:
    void init();
    void loop();

    GameConfig & configManager() { return m_gameConfig; }
    GameResourceManager & resourceManager() { return m_resourceManager; }
    Factory & factory() { return m_factory; }
    GameScene & gameScene() { return m_scene; }
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


public:
    sf::Vector2u getWindowSize(){return m_window.getSize();}


    /**/


    bool getIsShieldOn() const;
    bool getIsCollided() const;
    bool getIsBlockCollision() const;
    bool getIsEnemyCollision() const;
    bool getIsFirewallCollision () const;
    bool getIsShieldCollision() const;
    bool getIsKnifeCollision() const;
    bool getIsKnifeThrownCollision() const;
    int getMaxY() const;
    unsigned int getScore() const;
    int getHealth() const;
    void setScore(unsigned int s);
    void setHealth(int hp);


    // void collision();
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;

    //TODO spostare le funzioni nella classe di competenza
    void handleTxt();

    sf::Sound hamonEnemySound;
    sf::Sound emeraldEnemySound;
    sf::Sound fireEnemySound;
    sf::Music gameMusic;
    unsigned int score=0;
    sf::Text scoreTxt;
    sf::Text numScore;
    sf::Text lifeTxt;
    sf::Text numLife;
    sf::Text knivesTxt;
    sf::Text numKnives;
    sf::Text scoreB;
    sf::Text bestScoreTxt;
    sf::Text bestScoreB;
    sf::Text bestScoreNum;

    sf::Font font;
private:
    ////////////////////
    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;

    bool isShieldOn=false;
    bool isCollided=false;
    bool BlockCollision=false;
    bool EnemyCollision=false;
    bool FirewallCollision=false;
    bool KnifeCollision=false;
    bool ShieldPowerupCollision=false;
    bool KnivesPowerupCollision=false;

    int maxY;
    int n;

    unsigned int bestScore=0;

    /////////////////

    std::list<Observer*> observers;
};

#endif //JOJO_RUN_GAME_H
