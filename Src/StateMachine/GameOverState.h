//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_GAMEOVERSTATE_H
#define JOJO_RUN_GAMEOVERSTATE_H

#include <SFML/Audio.hpp>
#include "Widgets/ImageWidget.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ShapeWidget.h"
#include "InputManager.h"
#include "StateMachine/AbsGameState.h"


class GameOverState: public AbsGameState{

public:
    static GameOverState* instance();

    void init() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

protected:
    void onEnter() override;
    void onExit() override;

private:
    enum class Action {UserInput, ShowRecords};

    static GameOverState* m_instance;

    void createScreen();
    void showScore();
    void saveScore();
    void updateInput();

    Action       m_action = Action::UserInput;
    InputManager m_inputManager;
    Widget *     m_root = nullptr;
    TextWidget * m_input_label = nullptr;
    TextWidget * m_input_value = nullptr;
};


#endif //JOJO_RUN_GAMEOVERSTATE_H
