//
// Created by Niccolo on 17/02/2021.
//

#ifndef JOJO_RUN_INITSTATE_H
#define JOJO_RUN_INITSTATE_H

#include "StateMachine/AbsGameState.h"

class InitState: public AbsGameState {
private:
    static InitState* m_instance;

public:
    static InitState* instance();

protected:
    void onEnter() override;
};

#endif //JOJO_RUN_INITSTATE_H
