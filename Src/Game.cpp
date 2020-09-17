//
// Created by angiolo99 on 23/08/20.
//

#include "Game.h"

bool Game::getIsCollided() const {
    return isCollided;
}

float Game::getCreationRate() const {
    return creationRate;
}

Game::~Game() {
    blocks.clear();
    enemies.clear();
    firewalls.clear();
    powerups.clear();
}

void Game::createObj() {
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 5 == 0 && randomCreation() == 0 && !isImmortalityOn ) {
            std::unique_ptr<PowerUp> knife = factory.createPowerUp(PowerUpType::Knife);
            knife->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            powerups.emplace_back(move(knife));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 0 && !isImmortalityOn ) {
            std::unique_ptr<PowerUp> shield = factory.createPowerUp(PowerUpType::Knife);
            shield->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            powerups.emplace_back(move(shield));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            blocks.emplace_back(move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
            std::unique_ptr<FireWall> fireWall = factory.createFireWall(FireWallType::MovingWall);
            fireWall->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            firewalls.emplace_back(move(fireWall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (!isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            blocks.emplace_back(move(block));
            std::unique_ptr<FireWall> firewall = factory.createFireWall(FireWallType::StillWall);
            firewall->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            firewalls.emplace_back(move(firewall));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::createEnemy() {
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 4 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::HamonEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::EmeraldEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if (countCreation % 6 == 0 && randomCreation() == 0) {
            std::unique_ptr<Enemy> enemy = factory.createEnemy(EnemyType::FireEnemy);
            enemy->setPosition(sf::Vector2f(2 * map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        if(!isCreated){
            std::unique_ptr<Enemy> enemy= factory.createEnemy(EnemyType::StillEnemy);
            enemy->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            enemies.emplace_back(move(enemy));
            isCreated = true;
            enemyClk.restart();
            countCreation++;
        }
        isCreated = false;
    }
}

void Game::handleTxt() {
    //da implementare
}

void Game::deleteObject() {
    for (int i=0; i<blocks.size(); i++) {
        if (blocks[i]->getPosition().x + blocks[i]->getGlobalBounds().width < 0)
            blocks.erase(blocks.begin() + i);
    }

    for (int i=0; i<firewalls.size(); i++) {
        if (firewalls[i]->getPosition().x + firewalls[i]->getGlobalBounds().width < 0)
            firewalls.erase(firewalls.begin() + i);
    }

    for (int i=0; i<powerups.size(); i++) {
        if (powerups[i]->getPosition().x + powerups[i]->getGlobalBounds().width < 0)
            powerups.erase(powerups.begin() + i);
    }
}

void Game::deleteEnemy() {
    for (int i=0; i<enemies.size(); i++) {
        if (enemies[i]->getPosition().x + enemies[i]->getGlobalBounds().width < 0)
            enemies.erase(enemies.begin() + i);
    }
}

void Game::moveObject() {
    for (auto &b : blocks) {
        if (b->getIsMovingBlock()) {
            if (b->getPosition().y + b->getGlobalBounds().height >= map.getMapSize().y - ground ||
                b->getPosition().y <= 0)
                b->setBlockSpeedX(-b->getBlockSpeedX());
            b->move(-speed.x, b->getBlockSpeedX());
        } else
            b->move(-speed.x, 0);
    }
    for (auto &p : powerups) {
        if (p->getIsMovingPu()) {
            if (p->getPosition().y + p->getGlobalBounds().height >= map.getMapSize().y - ground ||
                p->getPosition().y <= 0)
                p->setSpeedPux(-p->getSpeedPux());
            p->move(-speed.x, p->getSpeedPux());
        } else
            p->move(-speed.x, 0);
    }

    for (auto &f : firewalls) {
        if (f->getIsMovingFW()) {
            if (f->getPosition().y + f->getGlobalBounds().height >= map.getMapSize().y - ground ||
                f->getPosition().y <= 0)
                f->setFireWallSpeedX(-f->getFWSpeedX());
            f->move(-speed.x, f->getFWSpeedX());
        } else
            f->move(-speed.x, 0);
    }
}

void Game::collision() {
    //da impementare
}

void Game::moveHero() {
    hero.setHeroPos(hero.getHeroPos().x, hero.getHeroPos().y + g);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        hero.setHeroPos(hero.getHeroPos().x, hero.getHeroPos().y - jump);
        if (isShieldOn)
            hero.setHeroTexture(playerShieldTexture);
        else
            hero.setHeroTexture(playerTexture);
        playerTexture.setSmooth(true);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (isShieldOn)
            hero.setHeroTexture(playerShieldTexture);
        else
            hero.setHeroTexture(blockTexture);
        blockTexture.setSmooth(true);
    }
    if (hero.getHeroPos().y + hero.getHeroSize().y >= map.getMapSize().y - ground)
        hero.setHeroPos(hero.getHeroPos().x, map.getMapSize().y - (hero.getHeroSize().y + ground));
    if (hero.getHeroPos().y <= top )
        hero.setHeroPos(hero.getHeroPos().x, top );
}

void Game::moveEnemy() {
    for (auto &e : enemies) {
        if (e->getIsMovingEnemy()) {
            if (e->getPosition().y + e->getGlobalBounds().height >= map.getMapSize().y - ground ||
                e->getPosition().y <= 0)
                e->setSpeed(-e->getSpeed());
            e->move(-speed.x, e->getSpeed());
        } else
            e->move(-speed.x, 0);
}









