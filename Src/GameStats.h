//
// Created by Niccolo on 07/03/2021.
//

#ifndef JOJO_RUN_GAMESTATS_H
#define JOJO_RUN_GAMESTATS_H

#include <list>
#include <map>
#include <string>

#include "Subject.h"

class GameStats : public Subject {

public:
    void addScore(unsigned int delta) { m_score += delta; }

private:
    unsigned int m_score = 0;

public:
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;

private:
    std::list<Observer*> observers;
};


#endif //JOJO_RUN_GAMESTATS_H
