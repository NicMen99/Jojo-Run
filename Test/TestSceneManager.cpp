//
// Created by Niccolo on 10/04/2021.
//

#include "TestSceneManager.h"
#include "CollisionManager.h"
#include "Entity.h"

void TestSceneManager::clearAll() {
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

std::unique_ptr<Entity>& TestSceneManager::get_hero() {
    return m_hero;
}

std::unique_ptr<Entity>& TestSceneManager::get_scorehud() {
    return m_scorehud;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_background1() {
    return m_background1;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_background2() {
    return m_background2;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_background3() {
    return m_background3;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_background4() {
    return m_background4;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_platforms() {
    return m_platforms;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_obstacles() {
    return m_obstacles;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_enemies() {
    return m_enemies;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_powerups() {
    return m_powerups;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_bullets() {
    return m_bullets;
}

std::vector<std::unique_ptr<Entity>>& TestSceneManager::get_spawned_objects() {
    return m_spawned_objects;
}

void TestSceneManager::generateBackground() {
    return SceneManager::generateBackground();
}

bool TestSceneManager::generatePlatforms() {
    return SceneManager::generatePlatforms();
}

bool TestSceneManager::generateEnemies(bool gen) {
    return SceneManager::generateEnemies(gen);
}

bool TestSceneManager::generateObstacles(bool gen) {
    return SceneManager::generateObstacles(gen);
}

bool TestSceneManager::generatePowerups(bool gen) {
    return SceneManager::generatePowerups(gen);
}

void TestSceneManager::addSpawned(std::unique_ptr<Entity> & newObject) {
    SceneManager::addSpawned(newObject);
}

void TestSceneManager::collectSpawned() { SceneManager::collectSpawned();
}

void TestSceneManager::createEnemy(EntityType typ, sf::Vector2f pos) {
    SceneManager::createEnemy(typ, pos);
}

void TestSceneManager::createObstacle(EntityType typ, sf::Vector2f pos) {
    SceneManager::createObstacle(typ, pos);
}

void TestSceneManager::createPowerup(EntityType typ, sf::Vector2f pos) {
    SceneManager::createPowerup(typ, pos);
}

void TestSceneManager::createHero() {
    SceneManager::createHero();
}

void TestSceneManager::removeDestroyedObjects() {
    SceneManager::removeDestroyedObjects();
}

sf::FloatRect TestSceneManager::get_last_platform() {
    return m_last_platform;
}

void TestSceneManager::set_last_platform(sf::FloatRect last_platform) {
    m_last_platform = last_platform;
}

float TestSceneManager::get_platform_space() {
    return m_platform_space;
}

void TestSceneManager::set_platforms_count(int count) {
    m_platforms_count = count;
};
