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

    destroyObjects(m_background1);
    destroyObjects(m_background2);
    destroyObjects(m_background3);
    destroyObjects(m_background4);
    destroyObjects(m_platforms);
    destroyObjects(m_obstacles);
    destroyObjects(m_enemies);
    destroyObjects(m_powerups);
    destroyObjects(m_bullets);

    /*
     * Map Generator
     */
    generateBackground();
    generateMap();

    /*
     * Add spawened objects
     */
    for(auto & it : m_spawned_objects) {
        if (it->getGroup() == EntityGroup::Bullet) {
            m_bullets.emplace_back(std::move(it));
        }
    }
    m_spawned_objects.clear();

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

void SceneManager::addNewEntity(std::unique_ptr<Entity> & newObject) {
    m_spawned_objects.emplace_back(std::move(newObject));
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

void SceneManager::generateBackground(){
    if(m_background1.size() < 2) {
        if(m_background1.empty()) {
            auto bg = FACTORY.createBackground(EntityType::Sky);
            bg->setPosition({0.f, 0.f});
            m_background1.emplace_back(std::move(bg));
        }
        auto bg = FACTORY.createBackground(EntityType::Sky);
        bg->setPosition({m_background1.at(0)->getPosition().x + m_background1.at(0)->getBounds().width, 0.f});
        m_background1.emplace_back(std::move(bg));
    }
    if (m_background2.size() < 2) {
        if(m_background2.empty()) {
            auto bg = FACTORY.createBackground(EntityType::City);
            bg->setPosition({0.f, 0.f});
            m_background2.emplace_back(std::move(bg));
        }
        auto bg = FACTORY.createBackground(EntityType::City);
        bg->setPosition({m_background2.at(0)->getPosition().x + m_background2.at(0)->getBounds().width, 0.f});
        m_background2.emplace_back(std::move(bg));
    }
    if (m_background3.size() < 2) {
        if(m_background3.empty()) {
            auto bg = FACTORY.createBackground(EntityType::SkyScrapers);
            bg->setPosition({0.f, 0.f});
            m_background3.emplace_back(std::move(bg));
        }
        auto bg = FACTORY.createBackground(EntityType::SkyScrapers);
        bg->setPosition({m_background3.at(0)->getPosition().x + m_background3.at(0)->getBounds().width, 0.f});
        m_background3.emplace_back(std::move(bg));
    }
    if (m_background4.size() < 2) {
        if(m_background4.empty()) {
            auto bg = FACTORY.createBackground(EntityType::Bridge);
            bg->setPosition({0.f, 0.f});
            m_background4.emplace_back(std::move(bg));
        }
        auto bg = FACTORY.createBackground(EntityType::Bridge);
        bg->setPosition({m_background4.at(0)->getPosition().x + m_background4.at(0)->getBounds().width, 0.f});
        m_background4.emplace_back(std::move(bg));
    }
}

void SceneManager::generateMap() {

    /*
     * Ci sono tre livelli ad altezza fissa da mettere nel game config ok
     * I nemici sono sempre appoggiati su una piattaforma
     * I blocchi sono o poggiati sulla piattaforma o ad altezza di hero+x dalla piattaforma (mai sovrapposti con una piattaforma)
     * I powerup sono ad altezza x dalla piattaforma o tra due piattaforme (mai sovrapposti con una piattaforma)
     * si parte con una piattaforma origine 0,0 e lunga tutto lo schermo
     * ogni piattaforma dista 0 <= x <= 250 dalla precedente e salta di -1 / 0 / +1 livelli ok
     */

    float posx;
    float posy;
    float size;
    static float space = 0;

    Entity * last = nullptr;

    if(m_platforms.empty()){
        /*
         * Prima piattaforma
         */
        posx = 0;
        posy = CONFIG.getMBase();
        size = CONFIG.getWindowSize().x;
        std::vector<float> hchoice = {100, 200, 300, 400};
        space = hchoice[RAND(hchoice.size())];
    }
    else
    {
        /*
         * Piattaforme successive
         */
        last = m_platforms.back().get();
        if(CONFIG.getWindowSize().x - (last->getPosition().x + last->getBounds().width) < space)
            return;

        std::vector<float> vchoice;
        if(last->getPosition().y == CONFIG.getMBase()) {
            vchoice = {CONFIG.getMBase(), CONFIG.getMMiddle()};
        } else if (last->getPosition().y == CONFIG.getMTop()) {
            vchoice = {CONFIG.getMTop(), CONFIG.getMMiddle()};
        }
        else {
            vchoice = {CONFIG.getMTop(), CONFIG.getMMiddle(), CONFIG.getMBase()};
        }
        posy = vchoice[RAND(vchoice.size())];
        posx = CONFIG.getWindowSize().x;
        size = (float)(1 + RAND(2)) * last->getBounds().width;
        std::vector<float> hchoice = {100, 200, 300, 400};
        space = hchoice[RAND(hchoice.size())];
    }

    /*
     * Genera piattaforme
     */
    float sizex = 0;
    while (sizex < size) {
        Entity * prev = createPlatform({sizex + posx, posy});
        sizex += prev->getBounds().width;
    }

    /*
     * Genera nemici
     */
    if(m_enemies.empty()) {
        std::vector<EntityType> echoice = {EntityType::FireEnemy, EntityType::HamonEnemy, EntityType::EmeraldEnemy};
        createEnemy(echoice[RAND(echoice.size())], sf::Vector2f(posx+size*3/4, posy));
    }
        /*
         * Genera ostacoli
         */
    else if(m_obstacles.empty()) {
        std::vector<EntityType> ochoice = {EntityType::Wall, EntityType::Block};
        createObstacle(ochoice[RAND(ochoice.size())], sf::Vector2f(posx + size/2, posy));
    }
        /*
         * Genera PowerUps
         */
    else if (m_powerups.empty()) {
        std::vector<EntityType> pchoice = {EntityType::Weapon, EntityType::Shield};
        createPowerup(pchoice[RAND(pchoice.size())], sf::Vector2f(posx + size/2, posy));
    }
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

Entity * SceneManager::createPlatform(sf::Vector2f position) {
    auto pl = FACTORY.createPlatform(EntityType::Platform);
    pl->setPosition(position);
    m_platforms.emplace_back(std::move(pl));
    return m_platforms.back().get();
}

void SceneManager::createObstacle(EntityType ot, sf::Vector2f position) {
    auto bl = FACTORY.createObstacle(ot);
    if (ot == EntityType::Wall){
        bl->setPosition(sf::Vector2f(0, -bl->getBounds().height) + position);
    } else {
        bl->setPosition(sf::Vector2f(0, -2*bl->getBounds().height) + position);
    }
    m_obstacles.emplace_back(std::move(bl));
}

void SceneManager::createEnemy(EntityType et, sf::Vector2f position) {
    auto en = FACTORY.createEnemy(et);
    en->setPosition(sf::Vector2f(0, -en->getBounds().height) + position);
    m_enemies.emplace_back(std::move(en));
}

void SceneManager::createPowerup(EntityType pt, sf::Vector2f position) {
    auto pu = FACTORY.createPowerUp(pt);
    pu->setPosition(sf::Vector2f(0, -2*pu->getBounds().height) + position);
    m_powerups.emplace_back(std::move(pu));
}

void SceneManager::createHero() {
    auto * hero = new Hero();
    hero->init();
    hero->setPosition(sf::Vector2f(200.f, CONFIG.getMBase() - hero->getBounds().height));

    m_hero = std::unique_ptr<Entity>(hero);
}

void SceneManager::createScoreHUD() {
    auto * hud = new ScoreHUD();
    hud->init();
    m_scorehud = std::unique_ptr<ScoreHUD>(hud);
}

