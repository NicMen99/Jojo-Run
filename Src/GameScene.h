//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_GAMESCENE_H
#define JOJO_RUN_GAMESCENE_H

#include <random>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

enum class PlatformPosition{Bottom=0, Middle, Top};

class GameScene
{
public:
    GameScene()=default;
    virtual ~GameScene();
    void init();
public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);

private:
    int rand(int max) { std::uniform_int_distribution<int> d(0, max - 1); return d(m_gen);}
    static void destroyObjects(std::vector<std::unique_ptr<GameObject>> & items);
    void createBackgorund();
    GameObject * createPlatform(sf::Vector2f position);
    void createBlocks();
    void createEnemies();
    void createPowerup();
    void generateMap();

private:
    std::random_device m_rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 m_gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib;
    PlatformPosition m_lastSpawned;

public:
    // fino a quando non è migrato il collision manager
    std::vector<std::unique_ptr<GameObject>> m_backgrounds;
    std::vector<std::unique_ptr<GameObject>> m_platforms;
    std::vector<std::unique_ptr<GameObject>> m_blocks;
    std::vector<std::unique_ptr<GameObject>> m_enemies;
    std::vector<std::unique_ptr<GameObject>> m_powerups;
    std::vector<std::unique_ptr<GameObject>> m_bullets;
};


#endif //JOJO_RUN_GAMESCENE_H
