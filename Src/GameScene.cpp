//
// Created by Niccolo on 27/02/2021.
//

/*@TODO factory*/
#include "GameConfig.h"
#include "Background.h"
#include "Platform.h"
#include "Block.h"
#include "EmeraldEnemy.h"
#include "HamonEnemy.h"
#include "FireEnemy.h"
#include "Knife.h"
#include "Shield.h"
#include "FireWall.h"
#include "Weapon.h"

#include "GameScene.h"


GameScene::~GameScene() {
    m_backgrounds.clear();
    m_platforms.clear();
    m_blocks.clear();
    m_enemies.clear();
    m_powerups.clear();
}

void GameScene::init()
{
    createBackgorund();
}

void GameScene::update(int32_t delta_time) {
    destroyObjects(m_platforms);
    destroyObjects(m_blocks);
    destroyObjects(m_enemies);
    destroyObjects(m_powerups);
    destroyObjects(m_bullets);
    createPlatform();
    createBlocks();
    createEnemies();
    createPowerups();


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
    float speedx = GC->getSceneSpeed().x;
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

void GameScene::createPlatform() {
    static sf::Clock timer;
    static int count = 1;
    /**
     * Logica da pensare
     */
     if(timer.getElapsedTime().asSeconds() > 2
     && m_platforms.size() < 4) {
         auto * pl = new Platform("Platform");
         pl->init("Platform1", sf::Vector2f {0,0});
         if(0==count%3)
             pl->setPosition({1650,315});
         else if(0==count%5)
             pl->setPosition({1650,615});
         else
             pl->setPosition({1650,915});
         m_platforms.emplace_back(std::unique_ptr<GameObject>(pl));
         timer.restart();
         count++;
     }
}

void GameScene::createBlocks() {
    static sf::Clock timer;
    static int count = 0;
    /**
     * Logica da pensare
     */
    if(timer.getElapsedTime().asSeconds() > 4
    && m_blocks.size() < 3) {
        if(0==count%5) {
            auto * fw = new FireWall("Firewall");
            fw->init("fireWallTexture", {0.7,0.7}, sf::Vector2f {0,0});
            fw->setPosition({1650, 333});
            m_blocks.emplace_back(std::unique_ptr<GameObject>(fw));

        }
        else
        {
            auto * bl = new Block("Block");
            bl->init("blockTexture", {0.7,0.7}, sf::Vector2f {0,0});
            bl->setPosition({1650, 555});
            m_blocks.emplace_back(std::unique_ptr<GameObject>(bl));
        }
        count++;
        timer.restart();
    }


}

void GameScene::createEnemies() {
    static sf::Clock timer;
    static int count = 1;
    /**
     * Logica da pensare
     */
    if(timer.getElapsedTime().asSeconds() > 3
       && m_enemies.size() < 3) {
        if(1==count%3) {
            auto * en = new EmeraldEnemy("Emerald");
            en->init("emeraldEnemyTexture", {-1, 1}, sf::Vector2f {0, 0}, 90);
            en->setPosition({1650, 200});
            m_enemies.emplace_back(std::unique_ptr<GameObject>(en));
        }
        else
        if(2==count%3) {
            auto * en = new HamonEnemy("hamon");
            en->init("hamonEnemyTexture", {-1, 1}, sf::Vector2f {0, 0}, 90);
            en->setPosition({1650, 400});
            m_enemies.emplace_back(std::unique_ptr<GameObject>(en));
        }
        else {
            auto * en = new FireEnemy("Fire");
            en->init("fireEnemy", {-1, 1}, sf::Vector2f {0, 0}, 90);
            en->setPosition({1650, 600});
            m_enemies.emplace_back(std::unique_ptr<GameObject>(en));
        }
        count++;
        timer.restart();
    }
}

void GameScene::createPowerups() {
    static sf::Clock timer;
    static int count = 1;
    /**
     * Logica da pensare
     */
    if(timer.getElapsedTime().asSeconds() > 10
       && m_powerups.size() < 2) {
        if(1==count%3) {
            auto * en = new Shield("Shield");
            en->init("shieldPowerUpTexture", {0.2, 0.2}, sf::Vector2f {20, 0});
            en->setPosition({1650, 222});
            m_powerups.emplace_back(std::unique_ptr<GameObject>(en));
        }
        else
        if(2==count%3) {
            auto * en = new Weapon("Knife");
            en->init("knifeTexture", {1, 1}, sf::Vector2f {0, 0});
            en->setPosition({1650, 444});
            m_powerups.emplace_back(std::unique_ptr<GameObject>(en));
        }
        count++;
        timer.restart();
    }

}

void GameScene::createBullet(const sf::Vector2f & position) {
    auto * en = new Knife("Knife");
    en->init("knifeTexture", {50, 0}, sf::Vector2f {20, 0}, 100);
    en->setPosition(position);
    m_bullets.emplace_back(std::unique_ptr<GameObject>(en));
}

