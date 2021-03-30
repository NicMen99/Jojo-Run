//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "GameOverState.h"

GameOverState* GameOverState::m_instance = nullptr;

GameOverState* GameOverState::instance() {
    if(nullptr == m_instance){
        m_instance = new GameOverState;
        m_instance->init();
    }
    return m_instance;
}

void GameOverState::init() {
    // m_music.openFromFile(CONFIG.getAssetPath(""));
}

void GameOverState::onEnter() {
    createScreen();
    m_inputManager.init();
    m_inputManager.registerAll();
    SCORE.loadFromFile();
    m_action = Action::UserInput;
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
            showScore();
            m_action = Action::ShowRecords;
        }
        else if(m_inputManager.isKeyJustPressed(sf::Keyboard::Escape)) {
            m_action = Action::ShowRecords;
            showScore();
        }
    }
}

void GameOverState::render(sf::RenderWindow &window) {
    m_root->render(window);
}

/**/

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
    background->setTexture("GameOverScreen", CONFIG.getWindowSize());
    sf::Vector2f background_size = background->getSize();
    m_root->add(background);

    auto * message = new TextWidget("Message");
    message->setString("G A M E   O V E R");
    message->init(theme);
    sf::Vector2f label_size = message->getSize();
    message->setPosition({background_size.x / 2 - label_size.x / 2, 50});
    m_root->add(message);

    auto * score = new TextWidget("ScoreManager");
    score->setString("YOUR SCORE IS : " + std::to_string(STATS.getInt(Stats::Score)));
    score->init(theme);
    score->setPosition({background_size.x / 2 - label_size.x / 2,150});
    m_root->add(score);

    auto * input_label = new TextWidget("Input");
    input_label->setString("ENTER YOUR NICKNAME : " );
    input_label->init(theme);
    input_label->setPosition({background_size.x / 2 - input_label->getSize().x / 2, 200});
    m_root->add(input_label);

    auto * input_value = new TextWidget("Value");
    input_value->setString("");
    input_value->init(theme);
    input_value->setPosition({input_label->getSize().x, 0});
    input_label->add(input_value);
    m_input = input_value;
}

void GameOverState::showScore() {

    WidgetTheme theme;
    theme.font_name = "gameover";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    auto * menu = new TextWidget("Menu");
    menu->setString("[ R ] ESTART A NEW GAME\n[ Q ] UIT");
    menu->init(theme);
    sf::Vector2f menu_size = menu->getSize();
    menu->setPosition({CONFIG.getWindowSize().x / 2.f - menu_size.x / 2.f, CONFIG.getWindowSize().y - 200.0f});
    m_root->add(menu);

    auto * topfive = new ShapeWidget("TopFive");
    topfive->init(theme);
    topfive->setSize({CONFIG.getWindowSize().x - 200.f, 400.f});
    topfive->setFillColor(sf::Color(255, 255, 0, 64));
    topfive->setPosition({100,400});
    m_root->add(topfive);

    int count = 0;
    float posy = 10;
    for(const auto& record : SCORE.getScoreRecord()) {

        count ++;

        auto * rank = new TextWidget("Rank");
        rank->init(theme);
        rank->setString(std::to_string(count));
        rank->setPosition({10, posy});
        if(record.added) rank->setFillColor(sf::Color::Red);
        topfive->add(rank);

        auto * name = new TextWidget("Name");
        name->init(theme);
        name->setString(record.nickname);
        name->setPosition({100, posy});
        if(record.added) name->setFillColor(sf::Color::Red);
        topfive->add(name);

        auto * score = new TextWidget("ScoreManager");
        score->init(theme);
        score->setString(std::to_string(record.score));
        score->setPosition({600, posy});
        if(record.added) score->setFillColor(sf::Color::Red);
        topfive->add(score);

        posy += 10 + name->getSize().y;
        if(count >= 5)
            break;
    }

}

void GameOverState::saveScore() {
    if(!m_input->getString().empty()) {
        SCORE.setName(m_input->getString());
        SCORE.saveToFile();
    }
}

static const int MAX_NAME_SIZE = 16;
void GameOverState::updateInput() {
    sf::Keyboard::Key key = m_inputManager.getKeyJustPressed();
    if(key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        std::string input_value = m_input->getString();
        if(input_value.size() < MAX_NAME_SIZE) {
            m_input->setString(input_value + static_cast<char>('A' + key - sf::Keyboard::A));
        }
    }
    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        std::string input_value = m_input->getString();
        if(input_value.size() < MAX_NAME_SIZE) {
            m_input->setString(input_value + static_cast<char>('0' + key - sf::Keyboard::Num0));
        }
    }
    else if (key == sf::Keyboard::BackSpace || key == sf::Keyboard::Escape) {
        m_input->setString("");
    }
}