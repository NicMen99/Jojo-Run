//
// Created by Niccolo on 17/02/2021.
//

#include "GameStateMachine.h"


GameStateMachine::GameStateMachine(State initialState) {
    changeState(initialState);
}

void GameStateMachine::exec() {
    switchState();
}

