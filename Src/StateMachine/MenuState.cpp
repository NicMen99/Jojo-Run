//
// Created by Niccolo on 23/03/2021.
//

#include "Game.h"
#include "MenuState.h"

MenuState* MenuState::m_instance = nullptr;

MenuState* MenuState::instance() {
    if(nullptr == m_instance){
        m_instance = new MenuState;
        m_instance->init();
    }
    return m_instance;
}

void MenuState::init() {
    // m_music.openFromFile(CONFIG.getAssetPath(""));
}

void MenuState::onEnter() {
    m_action = Action::MainMenu;
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::Num1);
    m_inputManager.registerKey(sf::Keyboard::Num2);
    m_inputManager.registerKey(sf::Keyboard::Escape);
    createMenuScreen();
    // m_music.setVolume(70.f);
    // m_music.play();
}

void MenuState::onExit() {
    // m_music.stop();
}

void MenuState::update(int32_t delta_time) {
    m_inputManager.update();
    if(m_action == Action::MainMenu) {
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::Num1))
            changeState(State::Play);
        else if(m_inputManager.isKeyJustPressed(sf::Keyboard::Num2)) {
            m_action = Action::Credits;
            createCreditScreen();
        }
        else if(m_inputManager.isKeyJustPressed(sf::Keyboard::Escape))
            exit(0);
    }
    else if (m_action == Action::Credits) {
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::Escape)) {
            m_action = Action::MainMenu;
            createMenuScreen();
        }
    }
}

void MenuState::render(sf::RenderWindow& window) {
    m_root->render(window);
}

void MenuState::createMenuScreen(){
    delete m_root;

    WidgetTheme theme;
    theme.font_name = "GAME_OVER_FONT";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * background = new ImageWidget("Background");
    background->init(theme);
    background->setTexture("SPLASH_SCREEN", {280,170});
    background->setPosition((CONFIG->getWindowSize().x-280.f)/2, 100);
    sf::Vector2f background_size = background->getSize();
    m_root->add(background);

    auto * mitem1 = new TextWidget("MenuItem1");
    mitem1->init(theme);
    mitem1->setString("[ 1 ]       ");
    mitem1->setFillColor(sf::Color::Red);
    mitem1->setPosition({CONFIG->getWindowSize().x/2.f - 150.f, CONFIG->getWindowSize().y * 0.35f});
    m_root->add(mitem1);

    auto * mlabel1 = new TextWidget("MenuLabel1");
    mlabel1->init(theme);
    mlabel1->setString("P L A Y");
    mlabel1->setPosition({mitem1->getSize().x, 0});
    mitem1->add(mlabel1);

    auto * mitem2 = new TextWidget("MenuItem2");
    mitem2->init(theme);
    mitem2->setString("[ 2 ]       ");
    mitem2->setFillColor(sf::Color::Red);
    mitem2->setPosition({CONFIG->getWindowSize().x/2.f - 150.f, CONFIG->getWindowSize().y * 0.4f});
    m_root->add(mitem2);

    auto * mlabel2 = new TextWidget("MenuLabel2");
    mlabel2->init(theme);
    mlabel2->setString("C R E D I T S");
    mlabel2->setPosition({mitem2->getSize().x, 0});
    mitem2->add(mlabel2);
}

void MenuState::createCreditScreen() {
    delete m_root;

    WidgetTheme theme;
    theme.font_name = "GAME_OVER_FONT";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * background = new ShapeWidget("Background");
    background->init(theme);
    background->setFillColor(sf::Color(0, 0, 0, 0));
    background->setSize(static_cast<sf::Vector2f>(CONFIG->getWindowSize()));
    sf::Vector2f overlay_size = background->getSize();
    m_root->add(background);

    std::ifstream infile(CONFIG->getAssetPath("CREDITS"));
    if(!infile.is_open())
        return;

    std::string line;
    float posy = 100;
    while (std::getline(infile, line)) {
        auto *rank = new TextWidget("");
        rank->init(theme);
        rank->setCharacterSize(100);
        rank->setString(line);
        rank->setPosition((CONFIG->getWindowSize().x - rank->getSize().x) / 2, posy);
        rank->setFillColor(sf::Color::Yellow);
        m_root->add(rank);
        posy += rank->getSize().y + 10.f;
    }
}
