//
// Created by Niccolo on 15/02/2021.
//


#include "Game.h"
#include "GameOverState.h"

/**/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
GameOverState* GameOverState::m_instance = nullptr;
sf::SoundBuffer gameOverBuffer;
sf::Sound gameOverSound;
sf::Texture gameOverTexture;
sf::Sprite gameOver;

std::ofstream file;
std::ofstream bestScoreFileWrite;
std::ifstream bestScoreFileRead;
unsigned int score;
unsigned int bestScore;
const int ground = 63.0f;
int txtCount;
/**/


void GameOverState::init() {
    sf::Vector2u window_size = GC.getWindowSize();
    gameOverBuffer.loadFromFile(GC.getAssetPath("gameOverSound"));
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(10.f);

    gameOverTexture.loadFromFile(GC.getAssetPath("GameOverScreen"));
    gameOver.setTextureRect(sf::IntRect(0,0,(window_size.x), window_size.y+static_cast<int>(ground)));
    gameOver.setTexture(gameOverTexture);
}

void GameOverState::onEnter() {
    gameOverSound.play();
//    m_context->gameMusic.stop();
}

void GameOverState::onExit() {
}

void GameOverState::update(int32_t delta_time) {
    file.open("Score.txt", std::ios::out | std::ios::app);
    file << std::endl;
    file << "Score: " << score;
    file.close();
    txtCount++;

    bestScoreFileRead.open("BestScore.txt");
    bestScoreFileRead >> bestScore;
    bestScoreFileRead.close();

    bestScoreFileWrite.open("BestScore.txt");
    if (score > bestScore) {
        bestScore = score;
    }
    bestScoreFileWrite.clear();
    bestScoreFileWrite << bestScore;
    bestScoreFileWrite.close();

}

void GameOverState::render(sf::RenderWindow &window) {
    window.draw(gameOver);
}

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}


