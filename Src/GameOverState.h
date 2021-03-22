//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_GAMEOVERSTATE_H
#define JOJO_RUN_GAMEOVERSTATE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ImageWidget.h"
#include "TextWidget.h"
#include "InputManager.h"
#include "Score.h"
#include "AbsGameState.h"

class GameOverState: public AbsGameState{

    enum class Action {UserInput, ShowRecords};

    static GameOverState* m_instance;
public:
    static GameOverState* instance();

public:
    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

private:
    void createScreen();
    void saveScore();
    void updateInput();

private:
    Action m_action = Action::UserInput;
    InputManager  m_inputManager;
    Score m_score;
    Widget * m_root = nullptr;
    TextWidget * m_input = nullptr;
};


#endif //JOJO_RUN_GAMEOVERSTATE_H
