//
// Created by Niccolo on 10/04/2021.
//

#include "MockSceneManager.h"
#include "CollisionManager.h"
#include "Entity.h"

void MockSceneManager::clearAll() {
    m_collisionManager.reset();
    m_background1.clear();
    m_background2.clear();
    m_background3.clear();
    m_background4.clear();
    m_platforms.clear();
    m_obstacles.clear();
    m_enemies.clear();
    m_powerups.clear();
    m_bullets.clear();
    m_spawned_objects.clear();
    m_hero.reset();
    m_scorehud.reset();
}

std::unique_ptr<Entity>& MockSceneManager::get_hero() {
    return m_hero;
}

std::unique_ptr<Entity>& MockSceneManager::get_scorehud() {
    return m_scorehud;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_background1() {
    return m_background1;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_background2() {
    return m_background2;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_background3() {
    return m_background3;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_background4() {
    return m_background4;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_platforms() {
    return m_platforms;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_obstacles() {
    return m_obstacles;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_enemies() {
    return m_enemies;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_powerups() {
    return m_powerups;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_bullets() {
    return m_bullets;
}

std::vector<std::unique_ptr<Entity>>& MockSceneManager::get_spawned_objects() {
    return m_spawned_objects;
}

void MockSceneManager::generateBackground() {
    return SceneManager::generateBackground();
}

bool MockSceneManager::generatePlatforms() {
    return SceneManager::generatePlatforms();
}

bool MockSceneManager::generateEnemies(bool gen) {
    return SceneManager::generateEnemies(gen);
}

bool MockSceneManager::generateObstacles(bool gen) {
    return SceneManager::generateObstacles(gen);
}

bool MockSceneManager::generatePowerups(bool gen) {
    return SceneManager::generatePowerups(gen);
}

void MockSceneManager::addSpawned(std::unique_ptr<Entity> & newObject) {
    SceneManager::addSpawned(newObject);
}

void MockSceneManager::collectSpawned() { SceneManager::collectSpawned();
}

void MockSceneManager::createEnemy(EntityType typ, sf::Vector2f pos) {
    SceneManager::createEnemy(typ, pos);
}

void MockSceneManager::createObstacle(EntityType typ, sf::Vector2f pos) {
    SceneManager::createObstacle(typ, pos);
}

void MockSceneManager::createPowerup(EntityType typ, sf::Vector2f pos) {
    SceneManager::createPowerup(typ, pos);
}

void MockSceneManager::createHero() {
    SceneManager::createHero();
}

void MockSceneManager::removeDestroyedObjects() {
    SceneManager::removeDestroyedObjects();
}

sf::FloatRect MockSceneManager::get_last_platform() {
    return m_last_platform;
}

void MockSceneManager::set_last_platform(sf::FloatRect last_platform) {
    m_last_platform = last_platform;
}

float MockSceneManager::get_platform_space() {
    return m_platform_space;
}

void MockSceneManager::set_platforms_count(int count) {
    m_platforms_count = count;
};
