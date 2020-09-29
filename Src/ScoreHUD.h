//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include "Observer.h"
#include "Game.h"
#include <fstream>
#include <iostream>

class Score: public Observer {
public:
    Score (Game* game);
    virtual ~Score() {detach();}

    void update() override;
    void attach() override;
    void detach() override;

protected:
    unsigned int score, health;
    Game* game;
};

#endif //JOJO_RUN_SCOREHUD_H
