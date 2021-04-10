//
// Created by Niccolo on 10/04/2021.
//

#ifndef JOJO_RUN_MOCKSCENEMANAGER_H
#define JOJO_RUN_MOCKSCENEMANAGER_H

#include "Game.h"

class MockSceneManager : public SceneManager {
public:
    void clearAll();
    std::unique_ptr<Entity>& get_hero();
    std::unique_ptr<Entity>& get_scorehud();
    std::vector<std::unique_ptr<Entity>>& get_background1();
    std::vector<std::unique_ptr<Entity>>& get_background2();
    std::vector<std::unique_ptr<Entity>>& get_background3();
    std::vector<std::unique_ptr<Entity>>& get_background4();
    std::vector<std::unique_ptr<Entity>>& get_platforms();
    std::vector<std::unique_ptr<Entity>>& get_obstacles();
    std::vector<std::unique_ptr<Entity>>& get_enemies();
    std::vector<std::unique_ptr<Entity>>& get_powerups();
    std::vector<std::unique_ptr<Entity>>& get_bullets();
    std::vector<std::unique_ptr<Entity>>& get_spawned_objects();
    void generateBackground();
    bool generatePlatforms();
    bool generateEnemies(bool gen);
    bool generateObstacles(bool gen);
    bool generatePowerups(bool gen);
    void addSpawned(std::unique_ptr<Entity> & newObject);
    void collectSpawned();
    void createEnemy(EntityType typ, sf::Vector2f pos);
    void createObstacle(EntityType typ, sf::Vector2f pos);
    void createPowerup(EntityType typ, sf::Vector2f pos);
    void createHero();
    void removeDestroyedObjects();
    sf::FloatRect get_last_platform();
    void set_last_platform(sf::FloatRect last_platform);
    float get_platform_space();
    void set_platforms_count(int count);
};

#endif //JOJO_RUN_MOCKSCENEMANAGER_H
