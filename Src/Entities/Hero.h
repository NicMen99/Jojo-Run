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
    void event(GameEvent event, Entity * entity) override;
    void update(int32_t delta_time) override;

private:
    enum class State {Init, Grounded, Jumping, Falling, Dead};

    void updatePhysics(int32_t delta_time);
    void speedCap();
    void manageAttack();
    void updateHealth(int delta);
    void updateKnives(int delta);
    void changeState(State new_state);

    State m_state = State::Init;
    InputManager m_inputManager;
    sf::Clock m_jumpTimer;
    int m_health = 0;
    int m_maxhealthpoints = 300;
    int m_knives = 2;
    int m_maxknives = 8;
    bool m_shield = false;
    float m_distance = 0;
    float m_clean_distance = 0;
    sf::Clock m_lifeTime;
};

#endif //JOJO_RUN_HERO_H
