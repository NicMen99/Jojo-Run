//
// Created by Niccolo on 17/02/2021.
//

#ifndef JOJO_RUN_GAMESTATEMACHINE_H
#define JOJO_RUN_GAMESTATEMACHINE_H

#include "AbsGameState.h"

class GameStateMachine : public AbsGameState {
public:
    GameStateMachine(Game* pContext, State initialState);
    void exec() override;
private:
    void update() override {getCurrentState()->update();}
    void render(sf::RenderWindow &window) override { getCurrentState()->render(window);}
};


#endif //JOJO_RUN_GAMESTATEMACHINE_H
