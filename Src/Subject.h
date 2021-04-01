//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SUBJECT_H
#define JOJO_RUN_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void subscribe (Observer * observer, const std::string & item_name) = 0;
    virtual void unsubscribe (Observer * observer, const std::string & item_name) = 0;
    virtual void notify(const std::string & item_value) = 0;
};


#endif //JOJO_RUN_SUBJECT_H
