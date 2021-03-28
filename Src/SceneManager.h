//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_SCENEMANAGER_H
#define JOJO_RUN_SCENEMANAGER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ScoreHUD.h"

enum class EnemyType;
enum class ObstacleType;
enum class PowerUpType;

class SceneManager
{
public:
    SceneManager()=default;
    virtual ~SceneManager() = default;
    void init();
public:
    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);
    bool levelend() const;
    void addNewEntity(std::unique_ptr<Entity> & newObject);

private:
    static void destroyObjects(std::vector<std::unique_ptr<Entity>> & items);
    void generateBackgorund();
    void generateMap();
    void manageCollisions();

    Entity * createPlatform(sf::Vector2f position);
    void createObstacle(GameObjectType ot, sf::Vector2f position);
    void createEnemy(GameObjectType et, sf::Vector2f position);
    void createPowerup(GameObjectType pt, sf::Vector2f position);
    void createHero();
    void createScoreHUD();

    bool collisionCheck(Entity * item1, Entity * item2);
    bool collisionHeroPlatformCheck(Entity * hero, Entity * platform);
    std::shared_ptr<sf::FloatRect> intersectionRect(Entity * hero, Entity * platform);


private:
    std::vector<std::unique_ptr<Entity>> m_background1;
    std::vector<std::unique_ptr<Entity>> m_background2;
    std::vector<std::unique_ptr<Entity>> m_background3;
    std::vector<std::unique_ptr<Entity>> m_background4;
    std::vector<std::unique_ptr<Entity>> m_platforms;
    std::vector<std::unique_ptr<Entity>> m_obstacles;
    std::vector<std::unique_ptr<Entity>> m_enemies;
    std::vector<std::unique_ptr<Entity>> m_powerups;
    std::vector<std::unique_ptr<Entity>> m_bullets;
    std::vector<std::unique_ptr<Entity>> m_spawned_objects;
    std::unique_ptr<Entity> m_hero;
    std::unique_ptr<ScoreHUD> m_scorehud;

private:
    unsigned long m_loops = 0;
};

#endif //JOJO_RUN_SCENEMANAGER_H
