//
// Created by angiolo99 on 29/01/20.
//
#ifndef JOJO_RUN_SHIELD_H
#define JOJO_RUN_SHIELD_H

#include "PowerUp.h"

class Shield final: public PowerUp {
public:
    Shield (std::string id);
    ~Shield() = default;
};

#endif //JOJO_RUN_SHIELD_H
