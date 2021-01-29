//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Subject.h"
#include "PowerUp.h"
#include <list>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite{
public:
    Hero ();
    virtual ~Hero() = default;

    bool gameOver();

    void setHeroTexture(const sf::Texture &heroTexture);

    sf::Vector2f getHeroSize() const;
    sf::Vector2f getHeroPos() const { return hero.getPosition(); }
    void setHeroPos(float x, float y) {hero.setPosition(x,y);}
    void renderHero(sf::RenderWindow &map);
    int getKnives() const;
    void setKnives(int knives);
    int getHealth() const;
    void setHealth (int hp);

    bool getIsDead() const {return isDead;}
    sf::FloatRect getHeroBounds() const { return hero.getGlobalBounds(); }

private:
    void death() {isDead = true;}

    int hp = 300;
    int knives = 0;
    bool isDead = false;
    sf::Sprite hero;
};

#endif //JOJO_RUN_HERO_H
