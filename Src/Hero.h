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
    void setHeroPos(float x, float y) {hero.setPosition(x,y);}
    bool getIsDead() const {return isDead;}
    bool getKnifeThrown() const {return knifeThrown;}
    void setKnifeThrown(bool a);
    void throwKnife();
    sf::Vector2f getHeroSize() const;
    sf::FloatRect getHeroBounds() const { return hero.getGlobalBounds(); }
    sf::Vector2f getHeroPos() const { return hero.getPosition(); }
    int getKnives() const;
    void setKnives(int knives);
    void renderHero(sf::RenderWindow &map);
    int getHealth() const;
    void setHealth (int hp);

private:
    void death() { isDead = true;}
    int hp = 300;
    bool isDead = false;
    bool knifeThrown = false;
    sf::Sprite hero;
    int knives = 0;
    unsigned int score;
    std::vector<std::unique_ptr<PowerUp>> powerups;
};

#endif //JOJO_RUN_HERO_H
