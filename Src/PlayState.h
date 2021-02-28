//
// Created by Niccolo on 15/02/2021.
//

#ifndef JOJO_RUN_PLAYSTATE_H
#define JOJO_RUN_PLAYSTATE_H

#include "AbsGameState.h"

class PlayState: public AbsGameState{
public:
    void init() override;
    void onEnter() override;
    void onExit() override;
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow &window) override;

public:
    static PlayState* instance();

private:
    static PlayState* m_instance;
};


#endif //JOJO_RUN_PLAYSTATE_H
