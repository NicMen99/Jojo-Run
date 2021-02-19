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

#include "Map.h"
#include "Hero.h"
#include "Factory.h"
#include "GameStateMachine.h"

class Game: public Subject {
    AbsGameState* m_gameMachine;
    sf::RenderWindow m_window;
    sf::Event m_event;
public:
    Game();
    ~Game();
    void init();
    void loop();
    sf::Vector2u getWindowSize(){return m_window.getSize();}
/////////////////

    int randomPosY();
    int randomCreation();


    //void update();
    //void render();

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
    int getBlocksSize() { return static_cast<int>(blocks.size()); };
    int getEnemySize() { return static_cast<int>(enemies.size()); };
    int getPowerUpSize() { return static_cast<int>(powerups.size()); };
    int getKnivesSize() { return static_cast<int>(knives.size()); };
    int getFireWallsSize() { return static_cast<int>(firewalls.size()); };


    void collision();
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;

    void createObj();
    void createEnemy();
    void moveObject();
    void moveHero();
    void throwKnife();
    void moveEnemy();
    void deleteObject();
    void deleteEnemy();
    void handleTxt();

    void setIsShieldOn(bool isShieldOn);
    void setBlockCollision(bool blockCollision);
    void setEnemyCollision(bool enemyCollision);
    void setFirewallCollision(bool firewallCollision);
    void setKnifeCollision(bool knifeCollision);
    void setShieldPowerupCollision(bool shieldPowerupCollision);
    void setKnivesPowerupCollision(bool knivesPowerupCollision);

    void setIsCollided(bool isCollided);


    sf::Texture heroTexture1;
    sf::Texture heroTexture2;
    sf::Texture heroTextureS1;

    sf::Sound collisionSound;
    sf::Sound powerUpSound;
    sf::Sound shieldOnSound;
    sf::Sound hamonEnemySound;
    sf::Sound emeraldEnemySound;
    sf::Sound fireEnemySound;
    sf::Music gameMusic;
    int txtCount;
    unsigned int score;
    sf::Clock collisionClk;
    std::vector<std::unique_ptr<Block>> blocks;
    int collidedblocks;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int collidedenemies;
    std::vector<std::unique_ptr<PowerUp>> powerups;
    int collidedpowerups;
    std::vector<std::unique_ptr<PowerUp>> knives;
    int collidedknives;
    sf::Clock shieldClk;
    sf::Clock scoreClk;
    std::vector<std::unique_ptr<FireWall>> firewalls;
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
    Hero hero;
    sf::Sprite layer1;
    sf::Sprite layer2;
    sf::Sprite layer3;
    sf::Sprite layer4;

    sf::Font font;


private:
    ////////////////////
    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;

    Factory factory;

    bool isCreated;
    bool isPUCreated;
    bool isShieldOn;
    bool isCollided;
    bool BlockCollision;
    bool EnemyCollision;
    bool FirewallCollision;
    bool KnifeCollision;
    bool ShieldPowerupCollision;
    bool KnivesPowerupCollision;

    int blockX;
    int maxY;
    int countCreation;
    int n;

    unsigned int bestScore;

    float creationRate;
    //float oldCreationRate; necessaria?
    float toll = 0.2;

    double jump = 2.3f;
    double g = 1;

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


    sf::Texture gameOverTexture;
    sf::Texture layer1Texture;
    sf::Texture layer2Texture;
    sf::Texture layer3Texture;
    sf::Texture layer4Texture;

    sf::Sprite gameOver;


    int collidedfirewalls;

    sf::Clock objectClk;
    sf::Clock enemyClk;
    sf::Clock controlPU;
    sf::Clock powerupClk;

    sf::Vector2f speed;
    sf::Vector2f oldSpeed;

    sf::Sound gameOverSound;


    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer collisionBuffer;
    sf::SoundBuffer powerUpBuffer;
    sf::SoundBuffer shieldOnBuffer;
    sf::SoundBuffer fireEnemyBuffer;
    sf::SoundBuffer emeraldEnemyBuffer;
    sf::SoundBuffer hamonEnemyBuffer;
    /////////////////

    std::list<Observer*> observers;
};

#endif //JOJO_RUN_GAME_H
