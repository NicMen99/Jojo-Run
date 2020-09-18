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

void Hero::setHP(unsigned int hp) {
    Hero::hp = hp;
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
      //da implementare (se il coltello colpisce un nemico, la salute si rigenera in parte)
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

void Hero::collisionPU() {
    //da implementare
}






