//
// Created by angiolo99 on 23/01/20.
//

#include "ScoreHUD.h"

void Score::update() {
    score = game->getScore();
    health = game->getHealth();
}

void Score::attach() {
    game->subscribe(this);
}

void Score::detach() {
    game->unsubscribe(this);
}

Score::Score(Game *game): game(game), score(0), health(0) {
    attach();
}

