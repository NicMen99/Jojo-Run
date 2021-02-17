//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_PLAYSTATE_H
#define JOJO_RUN_PLAYSTATE_H

#include "AbsGameState.h"

class PlayState: public AbsGameState{
public:
    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

public:
    static PlayState* instance();

private:
    static PlayState* m_instance;
};


#endif //JOJO_RUN_PLAYSTATE_H
