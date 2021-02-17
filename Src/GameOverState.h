//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_GAMEOVERSTATE_H
#define JOJO_RUN_GAMEOVERSTATE_H

#include "AbsGameState.h"

class GameOverState: public AbsGameState{
public:
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

public:
    static GameOverState* instance();
private:
    static GameOverState* m_instance;
};


#endif //JOJO_RUN_GAMEOVERSTATE_H
