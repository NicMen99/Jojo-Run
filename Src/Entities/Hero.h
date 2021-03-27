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
#include "Entities/PowerUp.h"
#include "Entity.h"
#include "InputManager.h"

class Hero final : public Entity {

    enum class State {Grounded, Jumping, Falling, Dead};

public:
    Hero ();
    ~Hero() override = default;

    void init();
    void update(int32_t delta_time) override;
private:
    void collision(Entity *collider) override;

private:
    void updatePhysics(int32_t delta_time);
    void speedCap();
    void update_health(int delta);
    void manageAttack();

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

    void updateKnives(int delta);
};

#endif //JOJO_RUN_HERO_H
