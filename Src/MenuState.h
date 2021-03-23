//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_MENUSTATE_H
#define JOJO_RUN_MENUSTATE_H

#include <SFML/Audio/Music.hpp>

#include "ImageWidget.h"
#include "TextWidget.h"
#include "ShapeWidget.h"
#include "InputManager.h"

#include "AbsGameState.h"

class MenuState: public AbsGameState {

    enum Action {MainMenu, Credits };

    static MenuState* m_instance;
public:
    static MenuState* instance();

public:
    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

private:
    void createMenuScreen();
    void createCreditScreen();

private:
    Action       m_action = Action::MainMenu;
    InputManager m_inputManager;
    sf::Music    m_music{};
    Widget *     m_root = nullptr;
};


#endif //JOJO_RUN_MENUSTATE_H
