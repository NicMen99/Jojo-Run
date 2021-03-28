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

    bool isDead() { return m_state == State::Dead; }

private:
    void collision(Entity *collider) override;
    void updatePhysics(int32_t delta_time);
    void speedCap();
    void manageAttack();

private:
    void update_health(int delta);
    void updateKnives(int delta);


private:
    State m_state = State::Falling;
    InputManager m_inputManager;

private:
    sf::Clock m_jumpTimer;
    sf::Time m_maxJumpTime = sf::milliseconds(700);

private:
    int m_health = 0;
    int m_maxhp = 300;
    int m_knives = 0;
    int m_maxknives = 8;
    bool m_shield = false;
};

#endif //JOJO_RUN_HERO_H
