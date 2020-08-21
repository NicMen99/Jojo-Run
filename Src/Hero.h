//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Subject.h"
#include <list>
#include <string>
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite, public Subject{
public:
    //domani continuo ad aggiungere roba
    Hero ();
    virtual ~Hero() = default;
    bool gameOver();
    void setHeroTexture(const sf::Texture &heroTexture);
    void setHeroPosition(float x, float y) {hero.setPosition(x,y);}
    void setHP(unsigned int hp);
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
private:
    void death() { isDead = true;}
    int hp = 300;
    bool isDead = false;
    sf::Sprite hero;
    int knives = 0;
    std::list<Observer*> observers;
};

#endif //JOJO_RUN_HERO_H
