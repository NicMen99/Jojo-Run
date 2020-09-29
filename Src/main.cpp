#include "Game.h"
#include "ScoreHUD.h"

#include <chrono>
#include <thread>
#include <time.h>

int main() {
    Game game;
    Score score = Score(&game);

    int FPS = 60;
    int MS_PER_FRAME = 16 /FPS;

    while (!game.getMap()->isClosed()) {
        double start = clock() / CLOCKS_PER_SEC;
        game.update();
        game.render();
        std::this_thread::sleep_for(std::chrono::milliseconds((int) start + MS_PER_FRAME - (clock() / CLOCKS_PER_SEC)));
    }
}