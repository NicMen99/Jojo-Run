//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameStats.h"
#include "GameResourceManager.h"
#include "GameOverState.h"

GameOverState* GameOverState::m_instance = nullptr;


void GameOverState::init() {
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Key::R);
    m_inputManager.registerKey(sf::Keyboard::Key::Q);

    /*
    sf::Vector2u window_size = GC.getWindowSize();
    gameOverBuffer.loadFromFile(GC.getAssetPath("gameOverSound"));
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(10.f);

    gameOverTexture.loadFromFile(GC.getAssetPath("GameOverScreen"));
    gameOver.setTextureRect(sf::IntRect(0,0,window_size.x, window_size.y));
    gameOver.setTexture(gameOverTexture);
     */
}

void GameOverState::onEnter() {
    m_scene.init();
//    gameOverSound.play();
//    m_context->gameMusic.stop();
}

void GameOverState::onExit() {
}

void GameOverState::update(int32_t delta_time) {
    m_scene.update(delta_time);
    m_inputManager.update();

    if(m_inputManager.isKeyJustPressed(sf::Keyboard::Q)) {
        exit(0);
    }
    else if(m_inputManager.isKeyJustPressed(sf::Keyboard::R)) {
        changeState(State::Play);
    }

    /*
    file.open("Score.txt", std::ios::out | std::ios::app);
    file << std::endl;
    file << "Score: " << score;
    file.close();

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
    */
}

void GameOverState::render(sf::RenderWindow &window) {
    m_scene.render(window);
}

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}

/**/

void GameOverScene::init() {

    delete m_root;

    WidgetTheme theme;
    theme.font_name = "gameover";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * background = new ImageWidget("Background");
    background->init(theme);
    background->setTexture("GameOverScreen", GC.getWindowSize());
    sf::Vector2f background_size = background->getSize();
    m_root->add(background);

    auto * label = new TextWidget("label");
    label->setString("G A M E   O V E R");
    label->init(theme);
    sf::Vector2f label_size = label->getSize();
    label->setPosition({background_size.x/2 - label_size.x/2,100});
    m_root->add(label);

    auto * score = new TextWidget("label");
    score->setString("YOUR SCORE IS : " + std::to_string(STATS.getInt("SCORE")));
    score->init(theme);
    sf::Vector2f score_size = score->getSize();
    score->setPosition({background_size.x/2 - score_size.x/2,200});
    m_root->add(score);

    auto * menu = new TextWidget("label");
    menu->setString("PRESS  [R]  TO START A NEW GAME\nPRESS  [Q] TO QUIT");
    menu->init(theme);
    sf::Vector2f menu_size = menu->getSize();
    menu->setPosition({background_size.x/2 - menu_size.x/2,GC.getWindowSize().y-200.0f});
    m_root->add(menu);

}

void GameOverScene::update(int32_t delta_time) {
    m_root->update(delta_time);
}

void GameOverScene::render(sf::RenderWindow & window) {
    m_root->render(window);
}
