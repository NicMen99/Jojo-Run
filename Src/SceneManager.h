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
    void addNewEntity(std::unique_ptr<Entity> & newObject);

private:
    static void destroyObjects(std::vector<std::unique_ptr<Entity>> & items);
    void generateBackground();
    void generateMap();
    void manageCollisions();

    Entity * createPlatform(sf::Vector2f position);
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
    std::unique_ptr<ScoreHUD> m_scorehud;

};

#endif //JOJO_RUN_SCENEMANAGER_H
