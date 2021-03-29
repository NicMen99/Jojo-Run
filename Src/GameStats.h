//
// Created by Niccolo on 07/03/2021.
//

#ifndef JOJO_RUN_GAMESTATS_H
#define JOJO_RUN_GAMESTATS_H

#include <list>
#include <map>
#include <string>

#include "Subject.h"


struct Stats {
    static const char * Time;
    static const char * Score;
    static const char * Health;
    static const char * Knives;
    static const char * Distance;
    static const char * Killed;
    static const char * ConsecutiveKilled;
    static const char * CleanDistance;
};

struct Achievements {
    static const char * Score;
    static const char * Distance;
    static const char * Killed;
    static const char * ConsecutiveKilled;
    static const char * CleanDistance;
};



class GameStats : public Subject {
public:
    void unsubscribe(Observer * observer, const std::string & item_name) override;
    void subscribe(Observer * observer, const std::string & item_name) override;
    void notify(const std::string & item_value) override;
private:
    std::map<std::string, std::list<Observer*>> m_observers;

public:
    void init();
    void setInt(const std::string & item_name, int item_value);
    int getInt(const std::string & item_name);
    void addInt(const std::string & item_name, int item_value);
    void notifyValue(const std::string & item_name, const std::string & item_value);

private:
    std::map<std::string, int> m_stats;
};


#endif //JOJO_RUN_GAMESTATS_H
