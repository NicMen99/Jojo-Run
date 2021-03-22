//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameStats.h"
#include "GameResourceManager.h"
#include "GameOverState.h"

GameOverState* GameOverState::m_instance = nullptr;

void GameOverState::render(sf::RenderWindow &window) {
    m_root->render(window);
}

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}


void GameOverState::init() {
    /*
    sf::Vector2u window_size = GC.getWindowSize();
    gameOverBuffer.loadFromFile(GC.getAssetPath("gameOverSound"));
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(10.f);
    */
}

void GameOverState::onEnter() {
    createScreen();
    m_inputManager.init();
    m_inputManager.registerAll();
    m_score.load();
    m_action = Action::UserInput;
//    gameOverSound.play();
}

void GameOverState::onExit() {
}

void GameOverState::update(int32_t delta_time) {
    m_root->update(delta_time);
    m_inputManager.update();

    if(m_action == Action::ShowRecords) {
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::Q)) {
            exit(0);
        }
        else if(m_inputManager.isKeyJustPressed(sf::Keyboard::R)) {
            changeState(State::Play);
        }
    }
    else if (m_action == Action::UserInput) {
        updateInput();
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::Enter)) {
            saveScore();
            m_action = Action::ShowRecords;
        }
        else if(m_inputManager.isKeyJustPressed(sf::Keyboard::Escape)) {
            m_action = Action::ShowRecords;
        }
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



void GameOverState::createScreen() {

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

    auto * message = new TextWidget("Message");
    message->setString("G A M E   O V E R");
    message->init(theme);
    sf::Vector2f label_size = message->getSize();
    message->setPosition({background_size.x / 2 - label_size.x / 2, 100});
    m_root->add(message);

    auto * score = new TextWidget("Score");
    score->setString("YOUR SCORE IS : " + std::to_string(STATS.getInt("SCORE")));
    score->init(theme);
    score->setPosition({background_size.x / 2 - label_size.x / 2,300});
    m_root->add(score);

    auto * input_label = new TextWidget("Input");
    input_label->setString("ENTER YOUR NICKNAME : " );
    input_label->init(theme);
    input_label->setPosition({background_size.x / 2 - input_label->getSize().x / 2, 350});
    m_root->add(input_label);

    auto * input_value = new TextWidget("Value");
    input_value->setString("");
    input_value->init(theme);
    input_value->setPosition({input_label->getSize().x, 0});
    input_label->add(input_value);
    m_input = input_value;

    auto * menu = new TextWidget("Menu");
    menu->setString("[ R ] ESTART A NEW GAME\n[ Q ] UIT");
    menu->init(theme);
    sf::Vector2f menu_size = menu->getSize();
    menu->setPosition({background_size.x/2 - menu_size.x/2,GC.getWindowSize().y-200.0f});
    m_root->add(menu);
}

void GameOverState::saveScore() {
    m_score.load();
    if(!m_input->getString().empty()) {
        Score::Record r = {
                m_input->getString(),
                STATS.getInt("SCORE")};
        m_score.add(r);
        m_score.save();
    }
}

void GameOverState::updateInput() {
    sf::Keyboard::Key key = m_inputManager.getKeyJustPressed();
    if(key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        std::string input_value = m_input->getString();
        if(input_value.size() < 8) {
            m_input->setString(input_value+static_cast<char>('A' + key));
        }
    }
    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        std::string input_value = m_input->getString();
        if(input_value.size() < 8) {
            m_input->setString(input_value + static_cast<char>('0' + key));
        }
    }
    else if (key == sf::Keyboard::BackSpace || key == sf::Keyboard::Escape) {
        m_input->setString("");
    }
}