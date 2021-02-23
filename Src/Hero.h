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

class Hero final {
public:
    Hero () = default;
    virtual ~Hero() = default;

    void init(const std::string &texture_name, sf::Vector2f position, int hp = 300, int knives = 0, int max_kinves = 8, int max_health = 300);
    void update();
    void renderHero(sf::RenderWindow &window);

    bool gameOver();
    void collisionevent();

    sf::Vector2f getHeroSize() const;
    sf::Vector2f getHeroPos() const { return m_sprite.getPosition(); }
    void setHeroPos(float x, float y) {m_sprite.setPosition(x,y);}

    int getKnives() const;
    void setKnives(int knives);
    int getHealth() const;
    void setHealth (int hp);
    int getMaxknives() const;
    void setMaxknives(int maxknives);
    int getMaxhp() const;
    void setMaxhp(int maxhp);
    void setShieldOn();
    void setStanding();
    void setJumpOn();

    bool getIsDead() const {return m_isDead;}
    sf::FloatRect getHeroBounds() const { return m_sprite.getGlobalBounds(); }
    /*
     * ThrowKnife()
     * MoveHero()
     * */

private:
    void setHeroTexture(const sf::Texture &heroTexture);

private:
    void death() { m_isDead = true;}

    int m_hp = 300;
    int m_knives = 0;
    int m_maxknives = 8;
    int m_maxhp = 300;
    bool m_isDead = false;
    sf::Sprite m_sprite;

    bool m_shield = false;
    sf::Sound m_collisionSound;
    sf::Sound m_powerUpSound;
    sf::Sound m_shieldOnSound;

};

#endif //JOJO_RUN_HERO_H
