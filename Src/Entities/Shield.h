//
// Created by angiolo99 on 29/01/20.
//
#ifndef JOJO_RUN_SHIELD_H
#define JOJO_RUN_SHIELD_H

#include "Entities/PowerUp.h"

class Shield final: public PowerUp {
public:
    explicit Shield (std::string id);
    ~Shield() override;
    void init();

public:
    void event(GameEvent event, Entity *collider) override;
};

#endif //JOJO_RUN_SHIELD_H
