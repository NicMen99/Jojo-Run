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
    hero.setScale(0.9, 0.9);
}

sf::Vector2f Hero::getHeroSize() const {
    float x = hero.getGlobalBounds().width;
    float y = hero.getGlobalBounds().height;
    return sf::Vector2f(x, y);
}

int Hero::getKnives() const {
    return knives;
}

void Hero::setKnives(int knives) {
    Hero::knives = knives;
}

void Hero::renderHero(sf::RenderWindow &map) {
    map.draw(hero);
}

int Hero::getHealth() const {
    return hp;
}

void Hero::setHealth(int hp) {
    Hero::hp = hp;
}






