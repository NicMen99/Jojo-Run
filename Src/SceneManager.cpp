//
// Created by Niccolo on 27/02/2021.
//

#include <vector>

#include "Game.h"
#include "Entities/Background.h"
#include "Entities/Hero.h"
#include "ScoreHUD.h"
#include "CollisionManager.h"
#include "SceneManager.h"


SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {

}


void SceneManager::init()
{
    m_collisionManager = std::unique_ptr<CollisionManager>();

    m_background1.clear();
    m_background2.clear();
    m_background3.clear();
    m_background4.clear();
    m_platforms.clear();
    m_obstacles.clear();
    m_enemies.clear();
    m_powerups.clear();
    m_bullets.clear();
    m_hero.reset();
    m_scorehud.reset();

    createHero();
    createScoreHUD();
}

void SceneManager::update(int32_t delta_time) {

    /*
     * Rimuove oggetti distrutti
     */
    removeDestroyedObjects();

    /*
     * Aggiungi oggetti generati
     */
    collectSpawned();

    generateBackground();

    /*
     * Ci sono tre livelli ad altezza fissa da mettere nel game config ok
     * I nemici sono sempre appoggiati su una piattaforma
     * I blocchi sono o poggiati sulla piattaforma o ad altezza di hero+x dalla piattaforma (mai sovrapposti con una piattaforma)
     * I powerup sono ad altezza x dalla piattaforma o tra due piattaforme (mai sovrapposti con una piattaforma)
     * si parte con una piattaforma origine 0,0 e lunga tutto lo schermo
     * ogni piattaforma dista 0 <= x <= 250 dalla precedente e salta di -1 / 0 / +1 livelli ok
     */

    /*
     * Genera Piattaforme
     */
    if(generatePlatforms()) {
        /*
         * Genera nemici o ostacoli o potenziamenti
         */
        generateEnemies() || generateObstacles() || generatePowerups();
    }

    /*
     * Map Update
     */
    m_hero->update(delta_time);
    for (auto & it : m_background1) {
        it->update(delta_time);
    }
    for (auto & it : m_background2) {
        it->update(delta_time);
    }
    for (auto & it : m_background3) {
        it->update(delta_time);
    }
    for (auto & it : m_background4) {
        it->update(delta_time);
    }
    for (auto & it : m_platforms) {
        it->update(delta_time);
    }
    for (auto & it : m_obstacles) {
        it->update(delta_time);
    }
    for (auto & it : m_enemies) {
        it->update(delta_time);
    }
    for (auto & it : m_powerups) {
        it->update(delta_time);
    }
    for (auto & it : m_bullets) {
        it->update(delta_time);
    }

    /*
     * Collisions
     */
    manageCollisions();

    /*
     * HUD
     */
    m_scorehud->update(delta_time);
}

void SceneManager::render(sf::RenderWindow & window) {
    for (auto & it : m_background1) {
        it->render(window);
    }
    for (auto & it : m_background2) {
        it->render(window);
    }
    for (auto & it : m_background3) {
        it->render(window);
    }
    for (auto & it : m_background4) {
        it->render(window);
    }
    for (auto & it : m_platforms) {
        it->render(window);
    }
    for (auto & it : m_obstacles) {
        it->render(window);
    }
    for (auto & it : m_enemies) {
        it->render(window);
    }
    for (auto & it : m_powerups) {
        it->render(window);
    }
    for (auto & it : m_bullets) {
        it->render(window);
    }
    m_hero->render(window);
    m_scorehud->render(window);
}

bool SceneManager::levelend() const {
    return dynamic_cast<Hero *>(m_hero.get())->isDead();
}

/**/
void SceneManager::collectSpawned() {
    for(auto & it : m_spawned_objects) {
        if (it->getGroup() == EntityGroup::Bullet) {
            m_bullets.emplace_back(std::move(it));
        }
    }
    m_spawned_objects.clear();
}

void SceneManager::addSpawned(std::unique_ptr<Entity> & newObject) {
    m_spawned_objects.emplace_back(std::move(newObject));
}

/**/
void SceneManager::generateBackground(){
    if(m_background1.size() < 2) {
        if(m_background1.empty()) {
            auto bg = FACTORY->createBackground(EntityType::Sky);
            bg->setPosition({0.f, 0.f});
            m_background1.emplace_back(std::move(bg));
        }
        auto bg = FACTORY->createBackground(EntityType::Sky);
        bg->setPosition({m_background1.at(0)->getPosition().x + m_background1.at(0)->getBounds().width, 0.f});
        m_background1.emplace_back(std::move(bg));
    }
    if (m_background2.size() < 2) {
        if(m_background2.empty()) {
            auto bg = FACTORY->createBackground(EntityType::City);
            bg->setPosition({0.f, 0.f});
            m_background2.emplace_back(std::move(bg));
        }
        auto bg = FACTORY->createBackground(EntityType::City);
        bg->setPosition({m_background2.at(0)->getPosition().x + m_background2.at(0)->getBounds().width, 0.f});
        m_background2.emplace_back(std::move(bg));
    }
    if (m_background3.size() < 2) {
        if(m_background3.empty()) {
            auto bg = FACTORY->createBackground(EntityType::SkyScrapers);
            bg->setPosition({0.f, 0.f});
            m_background3.emplace_back(std::move(bg));
        }
        auto bg = FACTORY->createBackground(EntityType::SkyScrapers);
        bg->setPosition({m_background3.at(0)->getPosition().x + m_background3.at(0)->getBounds().width, 0.f});
        m_background3.emplace_back(std::move(bg));
    }
    if (m_background4.size() < 2) {
        if(m_background4.empty()) {
            auto bg = FACTORY->createBackground(EntityType::Bridge);
            bg->setPosition({0.f, 0.f});
            m_background4.emplace_back(std::move(bg));
        }
        auto bg = FACTORY->createBackground(EntityType::Bridge);
        bg->setPosition({m_background4.at(0)->getPosition().x + m_background4.at(0)->getBounds().width, 0.f});
        m_background4.emplace_back(std::move(bg));
    }
}

bool SceneManager::generatePlatforms() {
    float posx;
    float posy;
    float size = 0;
    static float space = 0;

    if(m_platforms.empty()){
        /*
         * Prima piattaforma
         */
        posx = 0;
        posy = CONFIG->getBottomLevel();
        size = CONFIG->getWindowSize().x;
        space = 350;
    }
    else
    {
        /*
         * Piattaforme successive
         */
        Entity * last = m_platforms.back().get();
        if(CONFIG->getWindowSize().x - (last->getPosition().x + last->getBounds().width) < space)
            return false;

        /* Posizione x appena fuori dello schermo */
        posx = CONFIG->getWindowSize().x;

        /* dimensione */
        std::vector<float> horizontal_size = {0.5f * CONFIG->getWindowSize().x, 0.8f * CONFIG->getWindowSize().x, (float)CONFIG->getWindowSize().x};
        size = horizontal_size[RAND(horizontal_size.size())];

        /* Posizione y uno dei tre livelli */
        std::vector<float> vertical_position;
        if(last->getPosition().y == CONFIG->getBottomLevel()) {
            vertical_position = {CONFIG->getBottomLevel(), CONFIG->getMiddleLevel()};
        } else if(last->getPosition().y == CONFIG->getTopLevel()) {
            vertical_position = {CONFIG->getMiddleLevel(), CONFIG->getTopLevel()};
        } else {
            vertical_position = {CONFIG->getBottomLevel(), CONFIG->getMiddleLevel(), CONFIG->getTopLevel()};
        }
        posy = vertical_position[RAND(vertical_position.size())];

        /* spazio di salto */
        std::vector<float> horizontal_spacing = {150, 250, 375, 500};
        if(last->getPosition().y < posy) {
            horizontal_size.pop_back();
        }
        space = horizontal_spacing[RAND(horizontal_spacing.size())];
    }
    createPlatform(EntityType::StonePlatform, size, {posx, posy});
    return true;
}

bool SceneManager::generateEnemies() {
    if(m_enemies.empty()) {
        std::vector<EntityType> echoice = {EntityType::FireEnemy, EntityType::HamonEnemy, EntityType::EmeraldEnemy};
        createEnemy(echoice[RAND(echoice.size())], sf::Vector2f(m_last_platform.left+m_last_platform.width*3/4, m_last_platform.top));
        return true;
    }
    return false;
}

bool SceneManager::generateObstacles() {
    if(m_obstacles.empty()) {
        std::vector<EntityType> ochoice = {EntityType::Wall, EntityType::Block};
        createObstacle(ochoice[RAND(ochoice.size())], sf::Vector2f(m_last_platform.left+m_last_platform.width/2, m_last_platform.top));
        return true;
    }
    return false;
}

bool SceneManager::generatePowerups() {
    if (m_powerups.empty()) {
        std::vector<EntityType> pchoice = {EntityType::Weapon, EntityType::Shield};
        createPowerup(pchoice[RAND(pchoice.size())], sf::Vector2f(m_last_platform.left+m_last_platform.width/2, m_last_platform.top));
        return true;
    }
    return false;
}

void SceneManager::manageCollisions() {

    if(m_hero->isEnabled()) {
        /*
         * Collisione Eroe Piattaforma
         */
        for (auto & platform : m_platforms) {
            if(m_collisionManager->collisionCheck(m_hero.get(), platform.get()))
                m_hero->event(GameEvent::Collision, platform.get());
        }
        /*
         * Collisione Eroe Nemici
         */
        for (auto & enemy : m_enemies) {
            if (m_collisionManager->collisionCheck(m_hero.get(), enemy.get())) {
                m_hero->event(GameEvent::Collision, enemy.get());
                enemy->event(GameEvent::Collision, m_hero.get());
            }
        }
        /*
         * Collisione Eroe Ostacoli
         */
        for (auto & obstacle : m_obstacles) {
            if (m_collisionManager->collisionCheck(m_hero.get(), obstacle.get())) {
                m_hero->event(GameEvent::Collision, obstacle.get());
                obstacle->event(GameEvent::Collision, m_hero.get());
            }
        }
        /*
         * Collisione Eroe Potenziamenti
         */
        for (auto & powerup : m_powerups) {
            if (m_collisionManager->collisionCheck(m_hero.get(), powerup.get())) {
                m_hero->event(GameEvent::Collision, powerup.get());
                powerup->event(GameEvent::Collision, m_hero.get());
            }
        }
        /*
         * Collisione Eroe Proiettili
         */
        for (auto & bullet : m_bullets) {
            if (m_collisionManager->collisionCheck(m_hero.get(), bullet.get())) {
                m_hero->event(GameEvent::Collision, bullet.get());
                bullet->event(GameEvent::Collision, m_hero.get());
            }
        }
        /*
         * Collisione Nemici Proiettili
         */
        for (auto & bullet : m_bullets) {
            for(auto & enemy : m_enemies) {
                if (m_collisionManager->collisionCheck(enemy.get(), bullet.get())) {
                    enemy->event(GameEvent::Collision, bullet.get());
                    bullet->event(GameEvent::Collision, enemy.get());
                    m_hero->event(GameEvent::EnemyKilled, enemy.get());
                }
            }
        }
    }
}

/**/
void SceneManager::removeDestroyedObjects(){
    destroyObjects(m_background1);
    destroyObjects(m_background2);
    destroyObjects(m_background3);
    destroyObjects(m_background4);
    destroyObjects(m_platforms);
    destroyObjects(m_obstacles);
    destroyObjects(m_enemies);
    destroyObjects(m_powerups);
    destroyObjects(m_bullets);
}

void SceneManager::destroyObjects(std::vector<std::unique_ptr<Entity>> & items) {
    for (auto it = items.begin(); it != items.end();) {
        if ((*it)->isDestroyed()) {
            it = items.erase(it);
        }
        else {
            ++it;
        }
    }
}

/**/
void SceneManager::createPlatform(EntityType platformtype, float size, sf::Vector2f position) {
    m_last_platform = {position.x, position.y, 0, 0};
    while (m_last_platform.width < size) {
        auto pl = FACTORY->createPlatform(platformtype);
        pl->setPosition({m_last_platform.width + position.x, position.y});
        m_last_platform.width += pl->getBounds().width;
        m_last_platform.height += pl->getBounds().height;
        m_platforms.emplace_back(std::move(pl));
    }
}

void SceneManager::createObstacle(EntityType ot, sf::Vector2f position) {
    auto bl = FACTORY->createObstacle(ot);
    if (ot == EntityType::Wall){
        bl->setPosition(sf::Vector2f(0, -bl->getBounds().height) + position);
    } else {
        bl->setPosition(sf::Vector2f(0, -2*bl->getBounds().height) + position);
    }
    m_obstacles.emplace_back(std::move(bl));
}

void SceneManager::createEnemy(EntityType et, sf::Vector2f position) {
    auto en = FACTORY->createEnemy(et);
    en->setPosition(sf::Vector2f(0, -en->getBounds().height) + position);
    m_enemies.emplace_back(std::move(en));
}

void SceneManager::createPowerup(EntityType pt, sf::Vector2f position) {
    auto pu = FACTORY->createPowerUp(pt);
    pu->setPosition(sf::Vector2f(0, -2*pu->getBounds().height) + position);
    m_powerups.emplace_back(std::move(pu));
}

void SceneManager::createHero() {
    m_hero = FACTORY->createHero();
    m_hero->setPosition(sf::Vector2f(200.f, CONFIG->getBottomLevel() - m_hero->getBounds().height));
}

void SceneManager::createScoreHUD() {
    auto * hud = new ScoreHUD();
    hud->init();
    m_scorehud = std::unique_ptr<Entity>(hud);
}
