//
// Created by Niccolo on 15/02/2021.
//

#include "AbsGameState.h"
#include "Game.h"
#include "InitState.h"
#include "PlayState.h"
#include "GameOverState.h"

State AbsGameState::m_currentState = State::None;
State AbsGameState::m_nextState = State::None;
Game* AbsGameState::m_context = nullptr;

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
void AbsGameState::setContext(Game *pContext) {
    m_context = pContext;
}

AbsGameState* AbsGameState::getCurrentState() {
    switch(m_currentState) {
        case State::None:
        case State::Init:
            return InitState::instance();
        case State::Play:
            return PlayState::instance();
        case State::Over:
            return GameOverState::instance();
        case State::Splash:
        case State::Menu:
        case State::Pause:
            break;
    }

    static_assert(true, "Bad state");
    return nullptr;
}



