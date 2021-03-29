//
// Created by Niccolo on 07/03/2021.
//

#include "GameStats.h"


const char * Stats::Time                        = "TIME_STAT";
const char * Stats::Score                       = "SCORE_STAT";
const char * Stats::Distance                    = "DISTANCE_STAT";
const char * Stats::Health                      = "HEALTH_STAT";
const char * Stats::Knives                      = "KNIVES_STAT";
const char * Stats::Killed                      = "KILLED_STAT";
const char * Stats::ConsecutiveKilled           = "CONSECKILLED_STAT";
const char * Stats::CleanDistance               = "CLEANDISTANCE_STAT";
const char * Achievements::Score                = "SCORE_ACHIEVEMENT";
const char * Achievements::Distance             = "DISTANCE_ACHIEVEMENT";
const char * Achievements::Killed               = "KILLED_ACHIEVEMENT";
const char * Achievements::ConsecutiveKilled    = "CONSECKILLED_ACHIEVEMENT";
const char * Achievements::CleanDistance        = "CLEANDISTANCE_ACHIEVEMENT";


void GameStats::subscribe(Observer * observer, const std::string & item_name) {
    m_observers[item_name].emplace_back(observer);
}

void GameStats::unsubscribe(Observer * observer, const std::string & item_name) {
    m_observers[item_name].remove(observer);
}

void GameStats::notify(const std::string & item_name) {
    std::string val = std::to_string(m_stats[item_name]);
    for (auto it = std::begin(m_observers[item_name]); it != std::end(m_observers[item_name]); it++)
        (*it)->data_update(item_name, val);
}

void GameStats::init() {
    m_stats.clear();
    m_observers.clear();
}

void GameStats::setInt(const std::string & item_name, int item_value) {
    m_stats[item_name] = item_value;
    notify(item_name);
}

int GameStats::getInt(const std::string & item_name) {
    return m_stats[item_name];
}

void GameStats::addInt(const std::string & item_name, int item_value) {
    setInt(item_name, getInt(item_name) + item_value);
    notify(item_name);
}

void GameStats::notifyValue(const std::string & item_name, const std::string & item_value) {
    for (auto it = std::begin(m_observers[item_name]); it != std::end(m_observers[item_name]); it++)
        (*it)->data_update(item_name, item_value);
}
