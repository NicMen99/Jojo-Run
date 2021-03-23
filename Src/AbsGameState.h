//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_ABSGAMESTATE_H
#define JOJO_RUN_ABSGAMESTATE_H

#include <SFML/Graphics.hpp>
class Game;

enum class State{
    None,
    Init,
    Menu,
    Play,
    GameOver};


class AbsGameState {
public:
    virtual void init();
    virtual void exec(){}
    virtual void update(int32_t delta_time) {};
    virtual void render(sf::RenderWindow &window) {};

protected:
    static void changeState(State nextState);
    static void switchState(bool forceExec=false);
    static AbsGameState* getCurrentState();
    static void setContext(Game* pContext);
protected:
    virtual void onEnter() {}
    virtual void onExit() {}

private:
    static State m_currentState;
    static State m_nextState;
};


#endif //JOJO_RUN_ABSGAMESTATE_H
