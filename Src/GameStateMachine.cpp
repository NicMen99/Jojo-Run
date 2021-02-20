//
// Created by Niccolo on 17/02/2021.
//

#include "GameStateMachine.h"


GameStateMachine::GameStateMachine(Game* pContext, State initialState) {
    setContext(pContext);
    changeState(initialState);
}

void GameStateMachine::exec() {
    switchState();
}

