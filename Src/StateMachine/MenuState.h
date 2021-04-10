//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_MENUSTATE_H
#define JOJO_RUN_MENUSTATE_H

#include <SFML/Audio/Music.hpp>

#include "Widgets/ImageWidget.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ShapeWidget.h"
#include "InputManager.h"

#include "StateMachine/AbsGameState.h"

class MenuState: public AbsGameState {

public:
    static MenuState* instance();

    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

private:
    enum Action {MainMenu, Credits };

    static MenuState* m_instance;

    void createMenuScreen();
    void createCreditScreen();

    Action       m_action = Action::MainMenu;
    InputManager m_inputManager;
    Widget *     m_root = nullptr;
};


#endif //JOJO_RUN_MENUSTATE_H
