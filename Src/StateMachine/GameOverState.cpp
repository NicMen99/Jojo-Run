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
    m_music.openFromFile(CONFIG->getAssetPath("SOUND_TRACK"));
}

void GameOverState::onEnter() {
    createScreen();
    m_inputManager.init();
    m_inputManager.registerAll();
    SCORE->loadFromFile();
    m_action = Action::UserInput;
}

void GameOverState::onExit() {
    m_music.stop();
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
    theme.font_name = "GAME_OVER_FONT";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * background = new ImageWidget("Background");
    background->init(theme);
    background->setTexture("GAME_OVER_SCREEN", CONFIG->getWindowSize());
    sf::Vector2f background_size = background->getSize();
    m_root->add(background);

    auto * message = new TextWidget("Message");
    message->init(theme);
    message->setString("G A M E   O V E R");
    sf::Vector2f label_size = message->getSize();
    message->setPosition({background_size.x / 2 - label_size.x / 2, 0});
    message->setFillColor(sf::Color::Red);
    m_root->add(message);

    m_input_label = new TextWidget("NicknameInput");
    m_input_label->init(theme);
    m_input_label->setString("ENTER YOUR NICKNAME : " );
    m_root->add(m_input_label);

    m_input_value = new TextWidget("Nickname");
    m_input_value->init(theme);
    m_input_value->setString("");
    m_input_value->setPosition({m_input_label->getSize().x, 0});
    m_input_label->setPosition({(background_size.x - m_input_label->getSize().x - m_input_value->getSize().x) / 2, 150});
    m_input_label->add(m_input_value);
}

void GameOverState::showScore() {
    m_music.setVolume(50);
    m_music.setPitch(1.03);
    m_music.play();

    WidgetTheme theme;
    theme.font_name = "GAME_OVER_FONT";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    ScoreManager::Record score_record = SCORE->getScore();
    if(!score_record.nickname.empty()) {
        std::string message;
        if (score_record.rank>10) {
            message = "WELL DONE   " + score_record.nickname + "   ! ! !";

            auto * score = new TextWidget("ScoreRecap");
            score->init(theme);
            std::string recap =
                    "   YOUR RANK IS  "   + std::to_string(score_record.rank) +
                    "   YOUR SCORE IS  "  + std::to_string(score_record.score) +
                    "   YOU RUN FOR  "    + std::to_string(score_record.distance) + "mt" +
                    "   YOU KILLED  "     + std::to_string(score_record.killed) + " enemies" +
                    "   YOU PLAYED FOR  " + std::to_string(score_record.time / 60) + "m : "
                                           + std::to_string(score_record.time % 60) + "s";
            score->setString(recap);
            score->setCharacterSize(70);
            score->setFillColor(sf::Color::Green);
            score->setPosition({CONFIG->getWindowSize().x / 2.f - score->getSize().x / 2.f, 220});
            m_root->add(score);
        }
        else {
            message = "CONGRATULATIONS   " + score_record.nickname + "   YOU ARE IN THE TOP TEN ! ! !";
        }
        m_input_label->setString(message);
        m_input_value->setVisible(false);
        m_input_label->setPosition((CONFIG->getWindowSize().x - m_input_label->getSize().x)/2, m_input_label->getPosition().y);
    }

    auto * menu = new TextWidget("Menu");
    menu->init(theme);
    menu->setString("[ R ] ESTART A NEW GAME\n[ Q ] UIT");
    sf::Vector2f menu_size = menu->getSize();
    menu->setPosition({CONFIG->getWindowSize().x / 2.f - menu_size.x / 2.f, CONFIG->getWindowSize().y - 200.0f});
    m_root->add(menu);

    auto * toprank = new ShapeWidget("TopN");
    toprank->init(theme);
    toprank->setSize({CONFIG->getWindowSize().x - 200.f, 450.f});
    toprank->setFillColor(sf::Color(255, 255, 0, 64));
    toprank->setPosition({100, 350});
    m_root->add(toprank);

    const std::vector<std::pair<float, std::string>> & hcolumns = {
            { 10.f,   "RANK"            },
            { 100.f,  "NICKNAME"        },
            { 550.f,  "SCORE"           },
            { 700.f,  "DISTANCE"        },
            { 850.f,  "CLEAN\nDISTANCE" },
            { 1030.f, "KILLED"          },
            { 1130.f, "KILLED\nCOMBO"   },
            { 1250.f, "TIME"            }
    };
    float posy = -30.f;
    for(const auto& column : hcolumns) {
        auto * rank = new TextWidget("");
        rank->init(theme);
        rank->setCharacterSize(50);
        rank->setString(column.second);
        rank->setPosition({column.first, posy});
        rank->setFillColor(sf::Color::Cyan);
        toprank->add(rank);
    }

    posy = 0.f;
    float posy_delta = 0.f;
    for(const auto& record : SCORE->getScoreRecords()) {
        const std::vector<std::pair<float, std::string>> & columns = {
                { 10.f,   std::to_string(record.rank)           },
                { 100.f,  record.nickname                       },
                { 550.f,  std::to_string(record.score)          },
                { 700.f,  std::to_string(record.distance)       },
                { 850.f,  std::to_string(record.clean_distance) },
                { 1030.f, std::to_string(record.killed)         },
                { 1130.f, std::to_string(record.consec_killed)  },
                { 1250.f, std::to_string(record.time/60)+"m : "+std::to_string(record.time%60)+"s"           }
                };
        for(const auto& column : columns) {
            auto * rank = new TextWidget("");
            rank->init(theme);
            rank->setString(column.second);
            rank->setPosition({column.first, posy});
            if(record.added) rank->setFillColor(sf::Color::Red);
            toprank->add(rank);
            posy_delta = rank->getSize().y;
        }
        posy += posy_delta + 5.f;
        if(record.rank >= 10)
            break;
    }
}

void GameOverState::saveScore() {
    if(m_input_value != nullptr && !m_input_value->getString().empty()) {
        SCORE->setName(m_input_value->getString());
        SCORE->saveToFile();
    }
}

static const int MAX_NAME_SIZE = 16;
void GameOverState::updateInput() {
    sf::Keyboard::Key key = m_inputManager.getKeyJustPressed();
    if(key == sf::Keyboard::Unknown)
        return;
    if(m_input_label == nullptr || m_input_value == nullptr)
        return;
    if(key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        if( m_input_value->getString().size() < MAX_NAME_SIZE) {
            m_input_value->setString(m_input_value->getString() + static_cast<char>('A' + key - sf::Keyboard::A));
        }
    }
    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        if( m_input_value->getString().size() < MAX_NAME_SIZE) {
            m_input_value->setString(m_input_value->getString() + static_cast<char>('0' + key - sf::Keyboard::Num0));
        }
    }
    else if (key == sf::Keyboard::BackSpace || key == sf::Keyboard::Escape) {
        m_input_value->setString("");
    }
    m_input_label->setPosition((CONFIG->getWindowSize().x - m_input_label->getSize().x - m_input_value->getSize().x)/2, m_input_label->getPosition().y);
}

