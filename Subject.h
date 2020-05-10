//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SUBJECT_H
#define JOJO_RUN_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe (Observer* o) = 0;
    virtual void notify() = 0;
};


#endif //JOJO_RUN_SUBJECT_H
