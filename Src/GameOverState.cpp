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
    sf::Vector2u window_size = m_context->getWindowSize();
    gameOverBuffer.loadFromFile(GC->getAssetPath("gameOverSound"));
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(21.f);

    gameOverTexture.loadFromFile(GC->getAssetPath("GameOverScreen"));
    gameOver.setTextureRect(sf::IntRect(0,0,(window_size.x), window_size.y+static_cast<int>(ground)));
    gameOver.setTexture(gameOverTexture);
}

void GameOverState::onEnter() {
    gameOverSound.play();
    m_context->gameMusic.stop();
    m_context->hamonEnemySound.stop();
    m_context->emeraldEnemySound.stop();
    m_context->fireEnemySound.stop();
}

void GameOverState::onExit() {
}

void GameOverState::update() {
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

    m_context->scoreTxt.setCharacterSize(80);
    m_context->numScore.setCharacterSize(80);
    m_context->scoreTxt.setPosition(600, 400);
    m_context->numScore.setPosition(900, 400);
    m_context->scoreB.setPosition(500, 390);

    window.draw(m_context->scoreTxt);
    window.draw(m_context->numScore);
    window.draw(m_context->scoreB);
    window.draw(m_context->bestScoreTxt);
    window.draw(m_context->bestScoreB);
    window.draw(m_context->bestScoreNum);
}

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}


