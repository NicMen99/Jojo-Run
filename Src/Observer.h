//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_OBSERVER_H
#define JOJO_RUN_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;

    virtual void event(const std::string & value) = 0;
    virtual void attach(const std::string & key) = 0;
    virtual void detach(const std::string & key) = 0;
};

#endif //JOJO_RUN_OBSERVER_H
