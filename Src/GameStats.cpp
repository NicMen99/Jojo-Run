//
// Created by Niccolo on 07/03/2021.
//

#include "GameStats.h"


void GameStats::notify() {
    for (auto it = std::begin(observers); it != std::end(observers); it++)
        (*it)->event();
}

void GameStats::unsubscribe(Observer *o) {
    observers.remove(o);
}

void GameStats::subscribe(Observer *o) {
    observers.push_back(o);
}