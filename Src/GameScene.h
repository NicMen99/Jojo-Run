//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_GAMESCENE_H
#define JOJO_RUN_GAMESCENE_H

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
    virtual ~GameScene() = default;
    void init();
public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);
    void addItem(std::unique_ptr<GameObject> & newObject);

    bool levelend() const;


private:
    static void destroyObjects(std::vector<std::unique_ptr<GameObject>> & items);
    void generateBackgorund();
    GameObject * createPlatform(sf::Vector2f position);
    void createObstacle(GameObjectType ot, sf::Vector2f position);
    void createEnemy(GameObjectType et, sf::Vector2f position);
    void createPowerup(GameObjectType pt, sf::Vector2f position);
    void createHero();
    void createScoreHUD();

    void generateMap();
    void manageCollision();

private:
    std::vector<std::unique_ptr<GameObject>> m_background1;
    std::vector<std::unique_ptr<GameObject>> m_background2;
    std::vector<std::unique_ptr<GameObject>> m_background3;
    std::vector<std::unique_ptr<GameObject>> m_background4;
    std::vector<std::unique_ptr<GameObject>> m_platforms;
    std::vector<std::unique_ptr<GameObject>> m_obstacles;
    std::vector<std::unique_ptr<GameObject>> m_enemies;
    std::vector<std::unique_ptr<GameObject>> m_powerups;
    std::vector<std::unique_ptr<GameObject>> m_bullets;
    std::vector<std::unique_ptr<GameObject>> m_spawned_objects;
    std::unique_ptr<GameObject> m_hero;
    std::unique_ptr<ScoreHUD> m_scorehud;

private:
    unsigned long m_loops = 0;
};

#endif //JOJO_RUN_GAMESCENE_H
