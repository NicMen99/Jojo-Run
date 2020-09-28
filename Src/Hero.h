//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Subject.h"
#include "PowerUp.h"
#include "Game.h"
#include <list>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite, public Subject{
public:
    Hero ();
    virtual ~Hero() = default;

    bool gameOver();
    void setHeroTexture(const sf::Texture &heroTexture);
    void setHeroPos(float x, float y) {hero.setPosition(x,y);}
    bool getIsDead() const {return isDead;}
    bool getKnifeThrown() const {return knifeThrown;}
    void throwKnife();
    sf::Vector2f getHeroSize() const;
    sf::FloatRect getHeroBounds() const { return hero.getGlobalBounds(); }
    sf::Vector2f getHeroPos() const { return hero.getPosition(); }
    int getKnives() const;
    void setKnives(int knives);
    int randomPU();
    void renderHero(sf::RenderWindow &map);
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;
    int getHealth() const;
    int getScore() const;
    void setScore(int score);
    void setHealth(int hp);
    void collisionAndUpdate();

private:
    void death() { isDead = true;}
    int hp = 300;
    bool isDead = false;
    bool knifeThrown = false;
    Game game;
    sf::Sprite hero;
    sf::Texture playerTexture;
    sf::Clock scoreClk;
    sf::Clock collisionClk;
    int knives = 0;
    unsigned int score;
    std::list<Observer*> observers;
    std::vector<std::unique_ptr<PowerUp>> powerups;
};

#endif //JOJO_RUN_HERO_H
