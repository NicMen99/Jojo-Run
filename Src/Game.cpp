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
   //da implementare
}

void Game::createEnemy() {
    //da implementare
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




