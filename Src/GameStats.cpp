//
// Created by Niccolo on 07/03/2021.
//

#include "GameStats.h"


void GameStatAbsItem::notify() {
    for (auto it = std::begin(m_observers); it != std::end(m_observers); it++)
        (*it)->event(std::to_string(m_value));
}

void GameStatAbsItem::unsubscribe(Observer *o) {
    m_observers.remove(o);
}

void GameStatAbsItem::subscribe(Observer *o) {
    m_observers.push_back(o);
}

void GameStats::setInt(const std::string & key, int value) {
    m_stats[key].setValue(value);
    m_stats[key].notify();
}

int GameStats::getInt(const std::string & key) {
    return (int) m_stats[key].getValue();
}

void GameStats::addInt(const std::string & key, int value) {
    int result = getInt(key);
    result += value;
    setInt(key, result);
}

void GameStats::subscribe(Observer *o, const std::string & item_name) {
    m_stats[item_name].subscribe(o);
}

void GameStats::unsubscribe(Observer *o, const std::string & item_name) {
    m_stats[item_name].unsubscribe(o);
}


