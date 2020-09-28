//
// Created by angiolo99 on 23/01/20.
//

#include "Hero.h"

bool Hero::gameOver() {
    if (hp <= 0)
        death();
    return isDead;
}

Hero::Hero() {
    hero.setPosition(65,100);
}

void Hero::setHeroTexture(const sf::Texture &heroTexture){
    hero.setTexture(heroTexture);
    hero.setScale(0.20, 0.20);
}

sf::Vector2f Hero::getHeroSize() const {
    float x = hero.getGlobalBounds().width;
    float y = hero.getGlobalBounds().height;
    return sf::Vector2f();
}

int Hero::getKnives() const {
    return knives;
}

void Hero::setKnives(int knives) {
    Hero::knives = knives;
}

void Hero::throwKnife() {
    if (this->knives > 0){
        knifeThrown = true;
    }
}

int Hero::randomPU() {
    return (rand() % 2);
}

void Hero::renderHero(sf::RenderWindow &map) {
    map.draw(hero);
}

void Hero::notify() {
    for (auto i = std::begin(observers); i != std::end(observers); i++)
        (*i)->update();
}

void Hero::unsubscribe(Observer *o) {
    observers.remove(o);
}

void Hero::subscribe(Observer *o) {
    observers.push_back(o);
}

int Hero::getScore() const {
    return score;
}

int Hero::getHealth() const {
    return hp;
}

void Hero::setScore(int score) {
    Hero::score = score;
    notify();
}

void Hero::setHealth(int hp) {
    Hero::hp = hp;
    notify();
}

void Hero::collisionAndUpdate() {
    setScore(score);
    setHealth(getHealth());

    if (!getIsDead()) {
        game.collision();
    }
    if (game.getIsCollided()) {
        if (collisionClk.getElapsedTime().asSeconds() >= 0.8f) {
            if(game.getFireWallCollision() && getHealth() > 15){
                setHealth(getHealth() - 15);
                notify();
                game.setFireWallCollision(false);
            }
            if(game.getBlockCollision() && getHealth() > 90){
                setHealth(getHealth() - 70);
                notify();
                game.setBlockCollision(false);
            }
            if(game.getEnemyCollision() && getHealth() > 90){
                setHealth(getHealth() - 90);
                notify();
                game.setEnemyCollision(false);
            }
            if(game.getShieldPowerUpCollision()){

                notify();
                game.setEnemyCollision(false);
            }


            //manca roba sui power up, rimedierò domani
        }
        game.setIsCollided(false);
    }
}






