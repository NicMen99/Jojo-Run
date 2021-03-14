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

    enum class State {Grounded, Jumping, Falling, Dead};

public:
    Hero ();
    ~Hero() = default;

    void init();
    void init(const std::string &texture_name, int hp = 300, int knives = 0, int max_kinves = 8, int max_health = 300);
    void update(int32_t delta_time) override;
private:
    void collision(GameObject *collider) override;

private:
    void setTexture(const sf::Texture &heroTexture);
    void updatePhysics(int32_t delta_time);
    void speedCap();
    void update_health(int delta);

private:
    sf::Sprite m_sprite;
    sf::Sound m_collisionSound;
    sf::Sound m_powerUpSound;
    sf::Sound m_shieldOnSound;
private:
    State m_state = State::Falling;
    InputManager m_inputManager;
private:
    float m_jumpForce = 20.f;
    float m_initialJumpForce = m_jumpForce * 3;
    float m_jumpSpeedLimit = -500.f;
    float m_fallingSpeedLimit = 1000.f;
    sf::Clock m_jumpTimer;
    sf::Time m_maxJumpTime = sf::milliseconds(700);
private:
    int m_health = 0;
    int m_maxhp = 300;
private:
    int m_knives = 0;
    int m_maxknives = 8;
private:
    bool m_shield = false;

    /* @TODO:  refactor*/
public:
    bool gameOver();

};

#endif //JOJO_RUN_HERO_H
