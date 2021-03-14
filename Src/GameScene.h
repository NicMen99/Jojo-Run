//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_GAMESCENE_H
#define JOJO_RUN_GAMESCENE_H

#include <random>
#include <SFML/Graphics.hpp>


#include "GameObject.h"
#include "ScoreHUD.h"

enum class EnemyType;
enum class ObstacleType;
enum class PowerUpType;

class GameScene
{
public:
    GameScene()=default;
    virtual ~GameScene();
    void init();
public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);

    bool levelend() const;


private:
    int rand(int max) { std::uniform_int_distribution<int> d(0, max - 1); return d(m_gen);}
    static void destroyObjects(std::vector<std::unique_ptr<GameObject>> & items);
    void createBackgorund();
    GameObject * createPlatform(sf::Vector2f position);
    void createObstacle(ObstacleType ot, sf::Vector2f position);
    void createEnemy(EnemyType et, sf::Vector2f position);
    void createPowerup(PowerUpType pt, sf::Vector2f position);
    void createHero();
    void createScoreHUD();

    void generateMap();
    void manageCollision();


private:
    std::random_device m_rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 m_gen; //Standard mersenne_twister_engine seeded with rd()

private:
    std::vector<std::unique_ptr<GameObject>> m_backgrounds;
    std::vector<std::unique_ptr<GameObject>> m_platforms;
    std::vector<std::unique_ptr<GameObject>> m_obstacles;
    std::vector<std::unique_ptr<GameObject>> m_enemies;
    std::vector<std::unique_ptr<GameObject>> m_powerups;
    std::vector<std::unique_ptr<GameObject>> m_bullets;
    std::unique_ptr<GameObject> m_hero;
    std::unique_ptr<ScoreHUD> m_scorehud;

private:
    unsigned long m_loops = 0;
};

#endif //JOJO_RUN_GAMESCENE_H
