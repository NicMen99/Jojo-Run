#include <chrono>
#include <thread>
#include <time.h>

#include "GameConfig.h"
#include "Game.h"
#include "ScoreHUD.h"

int main() {
    GameConfig::instance()->init("Assets");
    Game game;
    Score score = Score(&game);
    game.init();
    game.loop();
}