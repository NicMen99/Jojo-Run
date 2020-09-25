//
// Created by angiolo99 on 23/08/20.
//

#ifndef JOJO_RUN_GAME_H
#define JOJO_RUN_GAME_H

#include <list>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Map.h"
#include "Hero.h"
#include "Factory.h"

class Game {
public:
    Game();
    ~Game();
    Map *getMap() { return &map;}

    int randomPosY();
    int randomCreation();
    int randomPU();

    void update();
    void render();

    const sf::Vector2f &getSpeed() const;
    int getMaxY() const;
    bool getIsCollided() const;
    float getCreationRate() const;

    //ci sono delle funzioni che derivano dall'observer ma bisogna far derivare la classe

private:
    void createObj();
    void createEnemy();
    void moveObject();
    void deleteObject();
    void deleteEnemy();
    void moveHero();
    void collision();
    void handleTxt();
    void moveEnemy();

    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;

    Map map;
    Hero hero;
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
    int txtCount;

    unsigned int score;
    unsigned int bestScore;

    float creationRate;
    float oldCreationRate;
    float toll = 0.2;

    double jump = 2.3f;
    double g = 1;

    const float ground = 63.0f;
    const float top = 68.0f;
    const float speedLimit = 9.f;
    const unsigned int speedMul =  5;
    const float creationLimit = 0.4;
    const float creationPlus = 0.035;
    const float speedPlus = 0.08;
    const float gPlus = 0.03;
    const float gLimit = 3.5;
    const float jumpLimit = 5.5;
    const float jumpPlus = 0.08;

    sf::Texture heroTexture1;
    sf::Texture heroTexture2;
    sf::Texture heroTextureS1;
    sf::Texture gameOverTexture;
    sf::Texture layer1Texture;
    sf::Texture layer2Texture;
    sf::Texture layer3Texture;
    sf::Texture layer4Texture;

    sf::Sprite gameOver;
    sf::Sprite layer1;
    sf::Sprite layer2;
    sf::Sprite layer3;
    sf::Sprite layer4;

    sf::Text scoreTxt;
    sf::Text lifeTxt;
    sf::Text bestScoreTxt;
    sf::Text scoreB;
    sf::Text numScore;
    sf::Text bestScoreB;
    sf::Text bestScoreNum;

    sf::Font font;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<FireWall>> firewalls;
    std::vector<std::unique_ptr<PowerUp>> powerups;
    std::vector<std::unique_ptr<PowerUp>> knives;

    sf::Clock objectClk;
    sf::Clock enemyClk;
    sf::Clock controlPU;
    sf::Clock speedClk;
    sf::Clock doubleClk;
    sf::Clock scoreClk;
    sf::Clock collisionClk;
    sf::Clock shieldClk;

    sf::Vector2f speed;
    sf::Vector2f oldSpeed;

    sf::Music gameMusic;

    sf::Sound gameOverSound;
    sf::Sound collisionSound;
    sf::Sound powerUpSound;
    sf::Sound shieldOnSound;

    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer collisionBuffer;
    sf::SoundBuffer powerUpBuffer;
    sf::SoundBuffer shieldOnBuffer;
};

#endif //JOJO_RUN_GAME_H
