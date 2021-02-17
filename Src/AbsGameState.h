//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_ABSGAMESTATE_H
#define JOJO_RUN_ABSGAMESTATE_H

class Game;

enum class State{
    None,
    Init,
    Splash,
    Menu,
    Play,
    Pause,
    Over};


class AbsGameState {
public:
    virtual void init();
    virtual void exec(){}
    virtual void update(){};
    virtual void render(){};

protected:
    static void changeState(State nextState);
    static void switchState(bool forceExec=false);
    static AbsGameState* getCurrentState();
    static void setContext(Game* pContext);
protected:
    virtual void onEnter() {}
    virtual void onExit() {}

protected:
    static Game * m_context;
private:
    static State m_currentState;
    static State m_nextState;
};


#endif //JOJO_RUN_ABSGAMESTATE_H
