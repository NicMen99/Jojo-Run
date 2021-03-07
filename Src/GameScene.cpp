//
// Created by Niccolo on 27/02/2021.
//

#include <vector>

#include "Game.h"
#include "GameResourceManager.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "Factory.h"
#include "Background.h"
#include "Hero.h"



GameScene::~GameScene() {
    m_backgrounds.clear();
    m_platforms.clear();
    m_obstacles.clear();
    m_enemies.clear();
    m_powerups.clear();
}

void GameScene::init()
{
    m_gen.seed(m_rd());
    createBackgorund();
    createHero();
}

void GameScene::update(int32_t delta_time) {
    destroyObjects(m_platforms);
    destroyObjects(m_obstacles);
    destroyObjects(m_enemies);
    destroyObjects(m_powerups);
    destroyObjects(m_bullets);

    /*Map Generator */
    generateMap();

    /*Map Update*/
    for (auto & it : m_backgrounds) {
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
    for (auto & it : m_backgrounds) {
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
}

void GameScene::destroyObjects(std::vector<std::unique_ptr<GameObject>> & items) {
    for (auto it = items.begin(); it != items.end();) {
        if ((*it)->isDestroyed()) {
            it = items.erase(it);
        }
        else {
            ++it;
        }
    }
}

void GameScene::createBackgorund(){
    float speedx = GC.getSceneSpeed().x;
    auto * bg = new Background("Sky");
    bg->init("BG", true, {7.4, 7.4}, {static_cast<float>(speedx*0.2),0});
    m_backgrounds.push_back(std::unique_ptr<GameObject>(bg));
    bg = new Background("City");
    bg->init("Background1", true, {7.4, 7.4}, {static_cast<float>(speedx*0.1),0});
    m_backgrounds.push_back(std::unique_ptr<GameObject>(bg));
    bg = new Background("SkyScrapers");
    bg->init("Foreground", true, {7.4, 7.4}, {static_cast<float>(speedx*0.05), 0});
    m_backgrounds.push_back(std::unique_ptr<GameObject>(bg));
    bg = new Background("Bridge");
    bg->init("Middle", true, {7.4, 7.4}, {0, 0});
    m_backgrounds.push_back(std::unique_ptr<GameObject>(bg));
}

GameObject * GameScene::createPlatform(sf::Vector2f position) {
    auto pl = GF.createMap(PlatformType::Large);
    pl->setPosition(position);
    m_platforms.emplace_back(std::move(pl));
    return m_platforms.back().get();
}


void GameScene::createObstacle(ObstacleType ot, sf::Vector2f position) {
    auto bl = GF.createObstacle(ot);
    if (ot == ObstacleType::Firewall){
        bl->setPosition(sf::Vector2f(0, -bl->getBounds().height) + position);
    } else {
        bl->setPosition(sf::Vector2f(0, -2*bl->getBounds().height) + position);
    }
    m_obstacles.emplace_back(std::move(bl));
}

void GameScene::createEnemy(EnemyType et, sf::Vector2f position) {
    auto en = GF.createEnemy(et);
    en->setPosition(sf::Vector2f(0, -en->getBounds().height) + position);
    m_enemies.emplace_back(std::move(en));
}

void GameScene::createPowerup(PowerUpType pt, sf::Vector2f position) {
    auto pu = GF.createPowerUp(pt);
    pu->setPosition(sf::Vector2f(0, -2*pu->getBounds().height) + position);
    m_powerups.emplace_back(std::move(pu));
}


void GameScene::createHero() {
    auto * hero = new Hero();
    hero->init();

    m_hero = std::unique_ptr<GameObject>(hero);
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
        space = hchoice[rand(hchoice.size())];
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
        posy = vchoice[rand(vchoice.size())];
        posx = GC.getWindowSize().x;
        size = (float)(1 + rand(2)) * last->getBounds().width;
        std::vector<float> hchoice = {100, 200, 300, 400};
        space = hchoice[rand(hchoice.size())];
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
        std::vector<EnemyType> echoice = {EnemyType::FireEnemy, EnemyType::HamonEnemy, EnemyType::EmeraldEnemy};
        createEnemy(echoice[rand(echoice.size())], sf::Vector2f(posx+size*3/4, posy));
    }
    /*
     * Genera ostacoli
     */
    else if(m_obstacles.empty()) {
        std::vector<ObstacleType> ochoice = {ObstacleType::Firewall, ObstacleType::Block};
        createObstacle(ochoice[rand(ochoice.size())], sf::Vector2f(posx + size/2, posy));
    }
    /*
     * Genera PowerUps
     */
    else if (m_powerups.empty()) {
        std::vector<PowerUpType> pchoice = {PowerUpType::Weapon, PowerUpType::Shield};
        createPowerup(pchoice[rand(pchoice.size())], sf::Vector2f(posx + size/2, posy));
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
    }

}

