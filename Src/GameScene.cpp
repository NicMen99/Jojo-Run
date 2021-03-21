//
// Created by Niccolo on 27/02/2021.
//

#include <vector>
#include <iostream>

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "GameStats.h"
#include "Factory.h"
#include "Background.h"
#include "Hero.h"
#include "ScoreHUD.h"


GameScene::~GameScene() {
    m_background1.clear();
    m_background2.clear();
    m_background3.clear();
    m_background4.clear();
    m_platforms.clear();
    m_obstacles.clear();
    m_enemies.clear();
    m_powerups.clear();
}

void GameScene::init()
{
    createBackgorund();
    createHero();
    createScoreHUD();
}

void GameScene::update(int32_t delta_time) {

    if(m_loops++ % 60 == 0)
        STATS.addInt("SCORE", 1);

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
    generateMap();

    /*
     * Add spawened objects
     */
    for(auto & it : m_spawned_objects) {
        if (it->getGroup() == GameObjectGroup::Bullet) {
            m_bullets.emplace_back(std::move(it));
        }
    }
    m_spawned_objects.clear();

    /*
     * Map Update
     * */
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
    m_hero->update(delta_time);

    /*
     * Collisions
     */
    manageCollision();
}

void GameScene::render(sf::RenderWindow & window) {
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

void GameScene::destroyObjects(std::vector<std::unique_ptr<GameObject>> & items) {
    for (auto it = items.begin(); it != items.end();) {
        if ((*it)->isDestroyed()) {
            // std::cout << it->get()->getName() << std::endl;
            it = items.erase(it);
        }
        else {
            ++it;
        }
    }
}

void GameScene::createBackgorund(){
    if(m_background1.size() < 2) {
        if(m_background1.empty()) {
            auto bg = GF.createBackground(BackgroundTpe::Sky);
            bg->setSpeed({GC.getSceneSpeed().x*0.2f, 0.f});
            bg->setPosition({0.f, 0.f});
            m_background1.emplace_back(std::move(bg));
        }
        auto bg = GF.createBackground(BackgroundTpe::Sky);
        bg->setSpeed({GC.getSceneSpeed().x*0.2f, 0.f});
        bg->setPosition({m_background1.at(0)->getPosition().x, 0.f});
        m_background1.emplace_back(std::move(bg));
    }
    if (m_background2.size() < 2) {
        if(m_background2.empty()) {
            auto bg = GF.createBackground(BackgroundTpe::City);
            bg->setSpeed({GC.getSceneSpeed().x*0.1f, 0.f});
            bg->setPosition({0.f, 0.f});
            m_background2.emplace_back(std::move(bg));
        }
        auto bg = GF.createBackground(BackgroundTpe::City);
        bg->setSpeed({GC.getSceneSpeed().x*0.1f, 0.f});
        bg->setPosition({m_background2.at(0)->getPosition().x, 0.f});
        m_background2.emplace_back(std::move(bg));
    }
    if (m_background3.size() < 2) {
        if(m_background3.empty()) {
            auto bg = GF.createBackground(BackgroundTpe::SkyScrapers);
            bg->setSpeed({GC.getSceneSpeed().x * 0.05f, 0.f});
            bg->setPosition({0.f, 0.f});
            m_background3.emplace_back(std::move(bg));
        }
        auto bg = GF.createBackground(BackgroundTpe::SkyScrapers);
        bg->setSpeed({GC.getSceneSpeed().x*0.05f, 0.f});
        bg->setPosition({m_background3.at(0)->getPosition().x, 0.f});
        m_background3.emplace_back(std::move(bg));
    }
    if (m_background4.size() < 2) {
        if(m_background4.empty()) {
            auto bg = GF.createBackground(BackgroundTpe::Bridge);
            bg->setSpeed({0.f, 0.f});
            bg->setPosition({0.f, 0.f});
            m_background4.emplace_back(std::move(bg));
        }
        auto bg = GF.createBackground(BackgroundTpe::Bridge);
        bg->setSpeed({0.f, 0.f});
        bg->setPosition({m_background4.at(0)->getPosition().x, 0.f});
        m_background4.emplace_back(std::move(bg));
    }
}

GameObject * GameScene::createPlatform(sf::Vector2f position) {
    auto pl = GF.createMap(PlatformType::Large);
    pl->setPosition(position);
    m_platforms.emplace_back(std::move(pl));
    return m_platforms.back().get();
}


void GameScene::createObstacle(GameObjectType ot, sf::Vector2f position) {
    auto bl = GF.createObstacle(ot);
    if (ot == GameObjectType::Wall){
        bl->setPosition(sf::Vector2f(0, -bl->getBounds().height) + position);
    } else {
        bl->setPosition(sf::Vector2f(0, -2*bl->getBounds().height) + position);
    }
    m_obstacles.emplace_back(std::move(bl));
}

void GameScene::createEnemy(GameObjectType et, sf::Vector2f position) {
    auto en = GF.createEnemy(et);
    en->setPosition(sf::Vector2f(0, -en->getBounds().height) + position);
    m_enemies.emplace_back(std::move(en));
}

void GameScene::createPowerup(GameObjectType pt, sf::Vector2f position) {
    auto pu = GF.createPowerUp(pt);
    pu->setPosition(sf::Vector2f(0, -2*pu->getBounds().height) + position);
    m_powerups.emplace_back(std::move(pu));
}

void GameScene::createHero() {
    auto * hero = new Hero();
    hero->init();

    m_hero = std::unique_ptr<GameObject>(hero);
}

void GameScene::createScoreHUD() {
    auto * hud = new ScoreHUD();
    hud->init();
    m_scorehud = std::unique_ptr<ScoreHUD>(hud);
}


bool GameScene::levelend() const {
    return dynamic_cast<Hero*>(m_hero.get())->gameOver();
}


void GameScene::generateMap() {

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

    GameObject * last = nullptr;

    if(m_platforms.empty()){
        /*
         * Prima piattaforma
         */
        posx = 0;
        posy = GC.getMBase();
        size = GC.getWindowSize().x;
        std::vector<float> hchoice = {100, 200, 300, 400};
        space = hchoice[RAND(hchoice.size())];
    }
    else
    {
        /*
         * Piattaforme successive
         */
        last = m_platforms.back().get();
        if(GC.getWindowSize().x - (last->getPosition().x + last->getBounds().width) < space)
            return;

        std::vector<float> vchoice;
        if(last->getPosition().y == GC.getMBase()) {
            vchoice = {GC.getMBase(), GC.getMMiddle()};
        } else if (last->getPosition().y == GC.getMTop()) {
            vchoice = {GC.getMTop(), GC.getMMiddle()};
        }
        else {
            vchoice = {GC.getMTop(), GC.getMMiddle(), GC.getMBase()};
        }
        posy = vchoice[RAND(vchoice.size())];
        posx = GC.getWindowSize().x;
        size = (float)(1 + RAND(2)) * last->getBounds().width;
        std::vector<float> hchoice = {100, 200, 300, 400};
        space = hchoice[RAND(hchoice.size())];
    }

    /*
     * Genera piattaforme
     */
    float sizex = 0;
    while (sizex < size) {
        GameObject * prev = createPlatform({sizex+posx, posy});
        sizex += prev->getBounds().width;
    }


    /*
     * Genera nemici
     */
    if(m_enemies.empty()) {
        std::vector<GameObjectType> echoice = {GameObjectType::FireEnemy, GameObjectType::HamonEnemy, GameObjectType::EmeraldEnemy};
        createEnemy(echoice[RAND(echoice.size())], sf::Vector2f(posx+size*3/4, posy));
    }
    /*
     * Genera ostacoli
     */
    else if(m_obstacles.empty()) {
        std::vector<GameObjectType> ochoice = {GameObjectType::Wall, GameObjectType::Block};
        createObstacle(ochoice[RAND(ochoice.size())], sf::Vector2f(posx + size/2, posy));
    }
    /*
     * Genera PowerUps
     */
    else if (m_powerups.empty()) {
        std::vector<GameObjectType> pchoice = {GameObjectType::Weapon, GameObjectType::Shield};
        createPowerup(pchoice[RAND(pchoice.size())], sf::Vector2f(posx + size/2, posy));
    }
}

void GameScene::manageCollision() {

    if(m_hero->isEnabled()) {
        /*
         * Collisione Eroe Piattaforma
         */
        for (auto & platform : m_platforms) {
            if (platform->isEnabled() && platform->getBounds().intersects(m_hero->getBounds())) {
                m_hero->collision(platform.get());
            }
        }
        /*
         * Collisione Eroe Nemici
         */
        for (auto & enemy : m_enemies) {
            if (enemy->isEnabled() && enemy->getBounds().intersects(m_hero->getBounds())) {
                m_hero->collision(enemy.get());
                enemy->collision(m_hero.get());
            }
        }
        /*
         * Collisione Eroe Ostacoli
         */
        for (auto & obstacle : m_obstacles) {
            if (obstacle->isEnabled() && obstacle->getBounds().intersects(m_hero->getBounds())) {
                m_hero->collision(obstacle.get());
                obstacle->collision(m_hero.get());
            }
        }
        /*
         * Collisione Eroe PowerUp
         */
        for (auto & powerup : m_powerups) {
            if (powerup->isEnabled() && powerup->getBounds().intersects(m_hero->getBounds())) {
                m_hero->collision(powerup.get());
                powerup->collision(m_hero.get());
            }
        }
        /*
         * Collisione Eroe Bullet
         */
        for (auto & bullet : m_bullets) {
            if (bullet->isEnabled() && bullet->getBounds().intersects(m_hero->getBounds())) {
                m_hero->collision(bullet.get());
                bullet->collision(m_hero.get());
            }
        }
        /*
         * Collisione Nemici Coltello
         */
        for (auto & bullet : m_bullets) {
            for(auto & enemy : m_enemies) {
                if (bullet->isEnabled() && bullet->getBounds().intersects(enemy->getBounds())) {
                    enemy->collision(bullet.get());
                    bullet->collision(enemy.get());

                }
            }
        }
    }

}

void GameScene::addItem(std::unique_ptr<GameObject> & newObject) {
    m_spawned_objects.emplace_back(std::move(newObject));
}


