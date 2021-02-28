#include "GameConfig.h"
#include "Game.h"
#include "ScoreHUD.h"

int main() {
    Game* game = Game::instance();
    Score score = Score(game); //@TODO da spostare
    game->init();
    game->loop();
}