//
// Created by Niccolo on 27/02/2021.
//

#ifndef JOJO_RUN_SCENEMANAGER_H
#define JOJO_RUN_SCENEMANAGER_H

#include <SFML/Graphics.hpp>
class Entity;
enum class EntityType;
class ScoreHUD;
class CollisionManager;

class SceneManager
{
public:
    SceneManager();
    virtual ~SceneManager();
    void init();

    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);
    bool levelend() const;
    void addSpawned(std::unique_ptr<Entity> & newObject);

protected:
    void removeDestroyedObjects();
    void destroyObjects(std::vector<std::unique_ptr<Entity>> & items);
    void collectSpawned();

    void generateBackground();
    bool generatePlatforms();
    bool generateEnemies(bool random=true);
    bool generateObstacles(bool random=true);
    bool generatePowerups(bool random=true);

    void manageCollisions();

    void createPlatform(EntityType platformtype, float size, sf::Vector2f position);
    void createObstacle(EntityType ot, sf::Vector2f position);
    void createEnemy(EntityType et, sf::Vector2f position);
    void createPowerup(EntityType pt, sf::Vector2f position);
    void createHero();
    void createScoreHUD();

    std::unique_ptr<CollisionManager> m_collisionManager;
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
    std::unique_ptr<Entity> m_scorehud;

    sf::FloatRect m_last_platform;
    float m_platform_space;
    int m_enemies_count;
    int m_obstacles_count;
    int m_powerups_count;
};

#endif //JOJO_RUN_SCENEMANAGER_H
