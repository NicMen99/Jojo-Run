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

#include "GameStateMachine.h"
#include "GameConfig.h"
#include "GameResourceManager.h"

#include "Map.h"
#include "Background.h"
#include "Hero.h"
#include "Factory.h"
#include "GameScene.h"

#define GC Game::instance()->configManager()
#define RM Game::instance()->resourceManager()
#define GF Game::instance()->factory()

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

    GameConfig& configManager() { return m_gameConfig; }
    GameResourceManager& resourceManager() { return m_resourceManager; }
    Factory& factory() { return m_factory; }

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Time m_accumulator = sf::Time::Zero;
    sf::Time m_framerate = sf::seconds(1.f/60.f);

private:
    AbsGameState* m_gameMachine;
    GameConfig m_gameConfig;
    GameResourceManager m_resourceManager;
    Factory m_factory;

    sf::Event m_event{};

public:
    sf::Vector2u getWindowSize(){return m_window.getSize();}

    Hero m_hero;
    GameScene m_scene;

    /**/
    int randomPosY();
    int randomCreation();

    const sf::Vector2f &getSpeed() const;
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
    float getCreationRate() const;
    void setScore(unsigned int s);
    void setHealth(int hp);
    int getEnemySize() { return static_cast<int>(m_scene.m_enemies.size()); };
    int getPowerUpSize() { return static_cast<int>(m_scene.m_powerups.size()); };
    int getKnivesSize() { return static_cast<int>(knives.size()); };


    void collision();
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;

    //TODO spostare le funzioni nella classe di competenza
    void moveHero();
    void throwKnife();
    void handleTxt();

    void setIsShieldOn(bool isShieldOn);
    void setBlockCollision(bool blockCollision);
    void setEnemyCollision(bool enemyCollision);
    void setFirewallCollision(bool firewallCollision);
    void setKnifeCollision(bool knifeCollision);
    void setShieldPowerupCollision(bool shieldPowerupCollision);
    void setKnivesPowerupCollision(bool knivesPowerupCollision);

    void setIsCollided(bool isCollided);

    sf::Sound hamonEnemySound;
    sf::Sound emeraldEnemySound;
    sf::Sound fireEnemySound;
    sf::Music gameMusic;
    int txtCount;
    unsigned int score=0;
    sf::Clock collisionClk;
    int collidedblocks{};
    int collidedenemies{};
    int collidedpowerups{};
    std::vector<std::unique_ptr<PowerUp>> knives;
    int collidedknives{};
    sf::Clock shieldClk;
    sf::Clock scoreClk;
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


    int collidedfirewalls{};
private:
    ////////////////////
    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;

    bool isCreated=false;
    bool isPUCreated{};
    bool isShieldOn=false;
    bool isCollided=false;
    bool BlockCollision=false;
    bool EnemyCollision=false;
    bool FirewallCollision=false;
    bool KnifeCollision=false;
    bool ShieldPowerupCollision=false;
    bool KnivesPowerupCollision=false;

    int blockX;
    int maxY;
    int countCreation;
    int n;

    unsigned int bestScore=0;

    float creationRate;
    //float oldCreationRate; necessaria?
    float toll = 0.2;

    double jump = 8.6f;
    double g = 4;

    const float ground = 63.0f;
    const float top = 68.0f;
    const float speedLimit = 9.f;
    const float creationLimit = 0.4;
    const float creationPlus = 0.035;
    const float speedPlus = 0.08;
    const float gPlus = 0.03;
    const float gLimit = 3.5;
    const float jumpLimit = 5.5;
    const float jumpPlus = 0.08;

    sf::Clock enemyClk;
    sf::Clock controlPU;
    sf::Clock powerupClk;

    sf::Vector2f speed;
    sf::Vector2f oldSpeed;

    /////////////////

    std::list<Observer*> observers;
};

#endif //JOJO_RUN_GAME_H
