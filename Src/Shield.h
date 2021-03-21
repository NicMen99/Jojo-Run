//
// Created by angiolo99 on 29/01/20.
//
#ifndef JOJO_RUN_SHIELD_H
#define JOJO_RUN_SHIELD_H

#include "PowerUp.h"

class Shield final: public PowerUp {
public:
    explicit Shield (std::string id);
    ~Shield() override = default;
    void init();

public:
    void collision(GameObject * collider) override;
};

#endif //JOJO_RUN_SHIELD_H
