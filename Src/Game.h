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
#include "Block.h"
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
    int getBlocksSize() { return static_cast<int>(blocks.size()); };
    bool getisImmortalityOn() const;
    int getScore() const;
    int getLives() const;
    bool getIsCollided() const;
    float getCreationRate() const;
    void setScore(unsigned int score);
    void setLives(unsigned int lives);

private:
    void createObj();
    void moveObject();
    void deleteObject();
    void moveHero();
    void collision();
    void handleTxt();

    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;
    Map map;
    Hero robot;
    Factory factory;
    bool isCreated;
    bool isShieldOn;
    bool isImmortalityOn;
    bool isCollided;
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
};

#endif //JOJO_RUN_GAME_H
