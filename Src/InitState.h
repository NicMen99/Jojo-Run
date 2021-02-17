//
// Created by Niccolo on 17/02/2021.
//

#ifndef JOJO_RUN_INITSTATE_H
#define JOJO_RUN_INITSTATE_H

class Game;

#include "AbsGameState.h"

class InitState: public AbsGameState {
public:
    void onEnter() override;

public:
    static InitState* instance();

private:
    static InitState* m_instance;

};

#endif //JOJO_RUN_INITSTATE_H
