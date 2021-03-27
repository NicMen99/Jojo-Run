//
// Created by Niccolo on 15/02/2021.
//

#include "Game.h"
#include "AbsGameState.h"
#include "InitState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameOverState.h"

State AbsGameState::m_currentState = State::None;
State AbsGameState::m_nextState = State::None;

void AbsGameState::changeState(State nextState) {
    m_nextState = nextState;
}

void AbsGameState::init() {
}

void AbsGameState::switchState(bool forceExec) {
    if(m_nextState != m_currentState) {
        getCurrentState()->onExit();
        m_currentState = m_nextState;
        getCurrentState()->onEnter();
    }
}

AbsGameState* AbsGameState::getCurrentState() {
    switch(m_currentState) {
        case State::None:
        case State::Init:
            return InitState::instance();
        case State::Menu:
            return MenuState::instance();
            break;
        case State::Play:
            return PlayState::instance();
        case State::GameOver:
            return GameOverState::instance();
    }

    static_assert(true, "Bad state");
    return nullptr;
}



