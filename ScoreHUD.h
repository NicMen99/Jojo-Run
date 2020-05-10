//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include "Observer.h"
#include "Hero.h"
#include <fstream>
#include <iostream>

class Score: public Observer {
public:
    Score (Hero* hero);
    virtual ~Score() {detach();}

    void update() override;
    void attach() override;
    void detach() override;

protected:
    unsigned int score, health;
    Hero* hero;
};

#endif //JOJO_RUN_SCOREHUD_H
