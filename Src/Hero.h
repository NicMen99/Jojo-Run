//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include <list>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Subject.h"
#include "PowerUp.h"
#include "GameObject.h"
#include "InputManager.h"

class Hero final : public GameObject {

    enum class State {Grounded, Jumping, Falling};

public:
    Hero ();
    ~Hero() = default;

    void init();
    void init(const std::string &texture_name, int hp = 300, int knives = 0, int max_kinves = 8, int max_health = 300);
    void update(int32_t delta_time) override;

private:
    void setTexture(const sf::Texture &heroTexture);
    void updatephysics(int32_t delta_time);

private:
    sf::Sprite m_sprite;
    State m_state = State::Falling;
    InputManager m_inputManager;

private:
    float m_jumpForce = 2.5;
    sf::Clock m_jumpTimer;



    /* @TODO:  refactor*/
public:
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
    void death() { m_isDead = true;}

    int m_hp = 300;
    int m_knives = 0;
    int m_maxknives = 8;
    int m_maxhp = 300;
    bool m_isDead = false;

    bool m_shield = false;
    sf::Sound m_collisionSound;
    sf::Sound m_powerUpSound;
    sf::Sound m_shieldOnSound;
};

#endif //JOJO_RUN_HERO_H
