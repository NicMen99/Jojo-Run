//
// Created by Niccolo on 07/03/2021.
//

#include "GameStats.h"


const std::string Stats::Time                        = "TIME_STAT";
const std::string Stats::Score                       = "SCORE_STAT";
const std::string Stats::Distance                    = "DISTANCE_STAT";
const std::string Stats::Health                      = "HEALTH_STAT";
const std::string Stats::Knives                      = "KNIVES_STAT";
const std::string Stats::Killed                      = "KILLED_STAT";
const std::string Stats::ConsecutiveKilled           = "CONSECKILLED_STAT";
const std::string Stats::CleanDistance               = "CLEANDISTANCE_STAT";
const std::string Achievements::Score                = "SCORE_ACHIEVEMENT";
const std::string Achievements::Distance             = "DISTANCE_ACHIEVEMENT";
const std::string Achievements::Killed               = "KILLED_ACHIEVEMENT";
const std::string Achievements::ConsecutiveKilled    = "CONSECKILLED_ACHIEVEMENT";
const std::string Achievements::CleanDistance        = "CLEANDISTANCE_ACHIEVEMENT";


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
