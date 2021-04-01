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
    }
    else if (m_action == Action::Credits) {
    }
}

void MenuState::render(sf::RenderWindow& window) {
    m_root->render(window);
}

void MenuState::createMenuScreen(){
    delete m_root;

    WidgetTheme theme;
    theme.font_name = "gameover";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * overlay = new ShapeWidget("Overlay");
    overlay->init(theme);
    overlay->setFillColor(sf::Color(0, 0, 0, 0));
    overlay->setSize(static_cast<sf::Vector2f>(CONFIG->getWindowSize()));
    sf::Vector2f overlay_size = overlay->getSize();
    m_root->add(overlay);

    auto * mitem1 = new TextWidget("MenuItem1");
    mitem1->init(theme);
    mitem1->setString("[ 1 ]    P L A Y");
    sf::Vector2f mitem1_size = mitem1->getSize();
    mitem1->setPosition({overlay_size.x/2 - 100.f, (overlay_size.y-mitem1_size.y)/2-100.f});
    m_root->add(mitem1);

    auto * mitem2 = new TextWidget("MenuItem2");
    mitem2->init(theme);
    mitem2->setString("[ 2 ]    C R E D I T S");
    sf::Vector2f mitem2_size = mitem2->getSize();
    mitem2->setPosition({overlay_size.x/2 - 100.f, (overlay_size.y-mitem2_size.y)/2 - 50.f});
    m_root->add(mitem2);
}

void MenuState::createCreditScreen() {
    //@TODO
}
