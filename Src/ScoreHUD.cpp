//
// Created by angiolo99 on 23/01/20.
//

#include "ScoreHUD.h"

void Score::update() {
    score = hero->getScore();
    health = hero->getHealth();
}

void Score::attach() {
    hero->subscribe(this);
}

void Score::detach() {
    hero->unsubscribe(this);
}

Score::Score(Hero *hero): hero(hero), score(0), health(0) {
    attach();
}

