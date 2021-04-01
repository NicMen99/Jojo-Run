//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_HERO_H
#define JOJO_RUN_HERO_H

#include "Entity.h"
#include "InputManager.h"

class Hero final : public Entity {

public:
    Hero ();
    ~Hero() override;

    void init();
    void update(int32_t delta_time) override;

    bool isDead() { return m_state == State::Dead; }

private:
    enum class State {Grounded, Jumping, Falling, Dead};


    void event(GameEvent event, Entity * entity) override;
    void updatePhysics(int32_t delta_time);
    void speedCap();
    void manageAttack();

    void updateHealth(int delta);
    void updateKnives(int delta);


    State m_state = State::Falling;
    InputManager m_inputManager;

    sf::Clock m_jumpTimer;

    int m_health = 0;
    int m_maxhealthpoints = 300;
    int m_knives = 2;
    int m_maxknives = 8;
    bool m_shield = false;
    float m_distance = 0;
};

#endif //JOJO_RUN_HERO_H
