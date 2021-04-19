//
// Created by Niccolo on 17/02/2021.
//

#ifndef JOJO_RUN_GAMESTATEMACHINE_H
#define JOJO_RUN_GAMESTATEMACHINE_H

#include "StateMachine/AbsGameState.h"

class GameStateMachine : public AbsGameState {

public:
    explicit GameStateMachine(State initialState);
    void exec() override;

    void update(int32_t delta_time) override { getCurrentState()->update(delta_time);}
    void render(sf::RenderWindow &window) override { getCurrentState()->render(window);}
};


#endif //JOJO_RUN_GAMESTATEMACHINE_H
