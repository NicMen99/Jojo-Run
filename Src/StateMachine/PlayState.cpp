//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "PlayState.h"

PlayState* PlayState::m_instance = nullptr;

PlayState* PlayState::instance() {
    if(nullptr == m_instance){
        m_instance = new PlayState;
        m_instance->init();
    }
    return m_instance;
}

void PlayState::init() {
    m_music.openFromFile(CONFIG->getAssetPath("SOUND_TRACK"));
}

void PlayState::onEnter() {
    m_action = Action::Play;
    m_inputManager.init();
    m_inputManager.registerKey(sf::Keyboard::P);
    STATS->init();
    SCORE->init();
    SCENE->init();
    createOverlay();
    m_music.setVolume(70.f);
    m_music.play();
}

void PlayState::onExit() {
    m_music.stop();
}

void PlayState::update(int32_t delta_time) {
    m_inputManager.update();
    if(m_action == Action::Play) {
        SCENE->update(delta_time);
        SCORE->update();
        if(SCENE->levelend()) {
            m_action = Action::End;
            m_timer.restart();
            m_music.stop();
        }
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::P)) {
            m_music.setVolume(30.f);
            m_action = Action::Pause;
        }
    }
    else if (m_action == Action::Pause) {
        if(m_inputManager.isKeyJustPressed(sf::Keyboard::P)) {
            m_music.setVolume(70.f);
            m_action = Action::Play;
        }
    }
    else /*if (m_action == Action::End)*/ {
        if(m_timer.getElapsedTime() > sf::seconds(1))
            changeState(State::GameOver);
    }
}

void PlayState::render(sf::RenderWindow& window) {
    SCENE->render(window);
    if(m_action == Action::Pause) {
        m_root->render(window);
    }
}

void PlayState::createOverlay() {
    delete m_root;

    WidgetTheme theme;
    theme.font_name = "RETRO_GAMING_FONT";
    theme.font_size = 32;
    theme.font_color = sf::Color::White;
    theme.font_outline_thinckness = 2;

    m_root = new Widget("Root");

    auto * overlay = new ShapeWidget("Overlay");
    overlay->init(theme);
    overlay->setFillColor(sf::Color(255, 255, 255, 100));
    overlay->setSize(static_cast<sf::Vector2f>(CONFIG->getWindowSize()));
    sf::Vector2f overlay_size = overlay->getSize();
    m_root->add(overlay);

    auto * message = new TextWidget("Message");
    message->init(theme);
    message->setString("P A U S E");
    sf::Vector2f message_size = message->getSize();
    message->setPosition({(overlay_size.x-message_size.x)/2, (overlay_size.y-message_size.y)/2});
    m_root->add(message);
}

