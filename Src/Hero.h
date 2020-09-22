//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Subject.h"
#include "PowerUp.h"
#include <list>
#include <string>
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite, public Subject{
public:
    Hero ();
    virtual ~Hero() = default;

    bool gameOver();
    void setHeroTexture(const sf::Texture &heroTexture);
    void setHeroPos(float x, float y) {hero.setPosition(x,y);}
    bool getIsDead() const {return isDead;}
    void throwKnife();
    sf::Vector2f getHeroSize() const;
    sf::FloatRect getHeroBounds() const { return hero.getGlobalBounds(); }
    sf::Vector2f getHeroPos() const { return hero.getPosition(); }
    int getKnives() const;
    void setKnives(int knives);
    void renderHero(sf::RenderWindow &map);
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;
    int getHealth() const;
    int getScore() const;
    void setScore(int score);
    void setHealth(int hp);
    void collisionPU();

    float og_pos_x; //da inizializzare nella creazione di game

private:
    void death() { isDead = true;}
    int hp = 300;
    bool isDead = false;
    sf::Sprite hero;
    sf::Texture playerTexture;
    int knives = 0;
    int score;
    std::list<Observer*> observers;
    std::vector<std::unique_ptr<PowerUp>> powerups;
};

#endif //JOJO_RUN_HERO_H
