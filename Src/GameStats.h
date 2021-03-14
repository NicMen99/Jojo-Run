//
// Created by Niccolo on 07/03/2021.
//

#ifndef JOJO_RUN_GAMESTATS_H
#define JOJO_RUN_GAMESTATS_H

#include <list>
#include <map>
#include <string>

#include "Subject.h"

class GameStatAbsItem : public Subject {
public:
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;

    void setValue(int value) { m_value = value; }
    int getValue() const { return m_value; }

private:
    std::list<Observer*> m_observers;
    int m_value;
};

class GameStats {

    std::map<std::string, GameStatAbsItem> m_stats;

public:
    void setInt(const std::string & key, int value);
    int getInt(const std::string &key);
    void addInt(const std::string & key, int value);


public:
    void unsubscribe(Observer *o, const std::string & item_name);
    void subscribe(Observer *o, const std::string & item_name);
public:
};


#endif //JOJO_RUN_GAMESTATS_H
