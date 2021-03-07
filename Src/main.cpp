#include "GameConfig.h"
#include "Game.h"

int main() {
    Game* game = Game::instance();
    game->init();
    game->loop();
}