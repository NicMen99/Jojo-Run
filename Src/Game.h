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

    // funzioni random

    int randomPosY();
    int randomCreation();
    int randomPU();

    void update();
    void render();

    //funzioni getter

    const sf::Vector2f &getSpeed() const;
    int getMaxY() const;
    bool getisImmortalityOn() const;
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
    void collisionResolution();
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
    bool isImmortalityOn;
    // sono necessari entrambi? perché non abbiamo shield e immortalità
    bool isCollided;
    bool BlockCollision;
    bool EnemyCollision;
    bool FirewallCollision;
    bool KnifeCollision;

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

    sf::Texture blockTexture;
    sf::Texture emeraldBlockTexture;
    sf::Texture emeraldEnemyTexture;
    sf::Texture fireEnemyTexture;
    sf::Texture fireWallTexture;
    sf::Texture hamonBlockTexture;
    sf::Texture hamonEnemyTexture;
    sf::Texture knifeTexture;
    sf::Texture playerShieldTexture;
    sf::Texture playerTexture;
    // mancano le texture per il game over e per la mappa, ma in realtà solo per il game over


    //Non ho idea di cosa servono, intanto li trascrivo e tiro su la funzione, a cancellare è un attimo
    sf::Text scoreTxt;
    sf::Text lifeTxt;
    sf::Text bestScoreTxt;

    sf::Font font;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<FireWall>> firewalls;
    std::vector<std::unique_ptr<PowerUp>> powerups;
    std::vector<std::unique_ptr<Knife>> knives;

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
};

#endif //JOJO_RUN_GAME_H
