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



GameScene::~GameScene() {
    m_backgrounds.clear();
    m_platforms.clear();
    m_blocks.clear();
    m_enemies.clear();
    m_powerups.clear();
}

void GameScene::init()
{
    m_gen.seed(m_rd());
    createBackgorund();
}

void GameScene::update(int32_t delta_time) {
    destroyObjects(m_platforms);
    destroyObjects(m_blocks);
    destroyObjects(m_enemies);
    destroyObjects(m_powerups);
    destroyObjects(m_bullets);

    /*Map Generator */
    //createPlatform();
    generateMap();
    createBlocks();
    createEnemies();
    createPowerup();

    /*Map Update*/
    for (auto & it : m_backgrounds) {
        it->update(delta_time);
    }
    for (auto & it : m_platforms) {
        it->update(delta_time);
    }
    for (auto & it : m_blocks) {
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

}

void GameScene::render(sf::RenderWindow & window) {
    for (auto & it : m_backgrounds) {
        it->render(window);
    }
    for (auto & it : m_platforms) {
        it->render(window);
    }
    for (auto & it : m_blocks) {
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
    pl->setPosition(sf::Vector2f(0, -pl->getBounds().height) + position);
    m_platforms.emplace_back(std::move(pl));
    return m_platforms.back().get();
}


void GameScene::createBlocks() {
    static sf::Clock timer;
    /**
     * Logica da pensare
     */
    std::uniform_int_distribution<int> dist(0,4);
    if(timer.getElapsedTime().asSeconds() > 3 && m_blocks.size() < 3) {
        if(0==dist(m_gen)) {
            auto fw = GF.createObstacle(ObstacleType::Firewall);
            fw->setPosition({1650, 333});
            m_blocks.emplace_back(std::move(fw));
        }
        else
        {
            auto bl = GF.createObstacle(ObstacleType::Block);
            bl->setPosition({1650, 555});
            m_blocks.emplace_back(std::move(bl));
        }
        timer.restart();
    }


}

void GameScene::createEnemies() {
    static sf::Clock timer;
    /**
     * Logica da pensare
     */
    std::uniform_int_distribution<int> dist(0,2);

    if(timer.getElapsedTime().asSeconds() > 5
       && m_enemies.size() < 3) {
        if(1==dist(m_gen)) {
            auto en = GF.createEnemy(EnemyType::EmeraldEnemy);
            en->setPosition({1650, 200});
            m_enemies.emplace_back(std::move(en));
        }
        else
        if(2==dist(m_gen)) {
            auto en = GF.createEnemy(EnemyType::HamonEnemy);
            en->setPosition({1650, 400});
            m_enemies.emplace_back(std::move(en));
        }
        else {
            auto en = GF.createEnemy(EnemyType::FireEnemy);
            en->setPosition({1650, 600});
            m_enemies.emplace_back(std::move(en));
        }
        timer.restart();
    }
}

void GameScene::createPowerup() {
    static sf::Clock timer;
    static int count = 1;
    /**
     * Logica da pensare
     */
    if(timer.getElapsedTime().asSeconds() > 10
       && m_powerups.size() < 2) {
        if(1==count%3) {
            auto  pu = GF.createPowerUp(PowerUpType::Shield);
            pu->setPosition({1650, 222});
            m_powerups.emplace_back(std::move(pu));
        }
        else
        if(2==count%3) {
            auto pu = GF.createPowerUp(PowerUpType::Weapon);
            pu->setPosition({1650, 444});
            m_powerups.emplace_back(std::move(pu));
        }
        count++;
        timer.restart();
    }

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

    GameObject * last = nullptr;

    if(m_platforms.empty()){
        posx = 0;
        size = GC.getWindowSize().x;
        m_lastSpawned = PlatformPosition::Bottom;
    }
    else
    {
        last = m_platforms.back().get();

        std::vector<float> hchoice = {100, 200, 300, 400};
        if(GC.getWindowSize().x - (last->getPosition().x + last->getBounds().width) < hchoice[rand(hchoice.size())])
            return;

        std::vector<PlatformPosition> vchoice;

        if(m_lastSpawned == PlatformPosition::Bottom) {
            vchoice = {PlatformPosition::Bottom, PlatformPosition::Middle};
        } else if (m_lastSpawned == PlatformPosition::Top) {
            vchoice = {PlatformPosition::Top, PlatformPosition::Middle};
        }
        else {
            vchoice = {PlatformPosition::Bottom, PlatformPosition::Middle, PlatformPosition::Top};
        }
        m_lastSpawned = vchoice[rand(vchoice.size())];
        posx = GC.getWindowSize().x;

        size = (float)(1 + rand(2)) * last->getBounds().width;
    }

    if(m_lastSpawned == PlatformPosition::Bottom)
        posy = GC.getMBase();
    else if(m_lastSpawned == PlatformPosition::Middle)
        posy = GC.getMMiddle();
    else
        posy = GC.getMTop();

    float sizex = 0;
    while (sizex < size) {
        GameObject * prev = createPlatform({sizex+posx, posy});
        sizex += prev->getBounds().width;
    }
}

