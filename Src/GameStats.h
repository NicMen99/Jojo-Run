//
// Created by Niccolo on 07/03/2021.
//

#ifndef JOJO_RUN_GAMESTATS_H
#define JOJO_RUN_GAMESTATS_H

#include <list>
#include <map>
#include <string>

#include "Subject.h"

class GameStats  : public Subject {
public:
    void unsubscribe(Observer * observer, const std::string & item_name) override;
    void subscribe(Observer * observer, const std::string & item_name) override;
    void notify(const std::string & item_name) override;
private:
    std::map<std::string, std::list<Observer*>> m_observers;

public:
    void clear();
    void setInt(const std::string & key, int value);
    int getInt(const std::string &key);
    void addInt(const std::string & key, int value);
private:
    std::map<std::string, int> m_stats;
};


#endif //JOJO_RUN_GAMESTATS_H
