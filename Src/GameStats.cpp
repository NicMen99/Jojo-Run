//
// Created by Niccolo on 07/03/2021.
//

#include "GameStats.h"


void GameStats::subscribe(Observer * observer, const std::string & item_name) {
    m_observers[item_name].emplace_back(observer);
}

void GameStats::unsubscribe(Observer * observer, const std::string & item_name) {
    m_observers[item_name].remove(observer);
}

void GameStats::notify(const std::string & item_name) {
    for (auto it = std::begin(m_observers[item_name]); it != std::end(m_observers[item_name]); it++)
        (*it)->event(std::to_string(m_stats[item_name]));
}

void GameStats::clear() {
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
