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
    static const std::string Time;
    static const std::string Score;
    static const std::string Health;
    static const std::string Knives;
    static const std::string Distance;
    static const std::string Killed;
    static const std::string ConsecutiveKilled;
    static const std::string CleanDistance;
};

struct Achievements {
    static const std::string Score;
    static const std::string Distance;
    static const std::string Killed;
    static const std::string ConsecutiveKilled;
    static const std::string CleanDistance;
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
